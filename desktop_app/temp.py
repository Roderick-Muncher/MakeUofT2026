#code for generating random force
#display spike of force, value of force, force vs time graph on computer screen
#change of peak of force (instantaneous)
#long time of pause between forces like more than 15s than record time where pause happens

import time
from random import randint
import pygame
import matplotlib
matplotlib.use("Agg")  # IMPORTANT: draw off-screen (no Matplotlib window)
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas

start_time = time.time()

time_x = []
force_y = []
WINDOW = 10
pause = False
pause_start = 0
force_feedback = ""
cpm_text = ""
avg_force_text = ""
pause_warnings = []
pause_surfs = []


def find_local_maxima(data):
    local_max_indices = []
    if len(data) < 3:
        return local_max_indices

    for i in range(1, len(data) - 1):
        if data[i - 1] < data[i] > data[i + 1]:
            local_max_indices.append(i)

    return local_max_indices

fig = Figure(figsize=(7, 4), dpi=100)  # ~700x400 px
canvas = FigureCanvas(fig)
ax = fig.add_subplot(111)

ax.set_facecolor("#EDE5E8")
(line,) = ax.plot([], [], color="#D0538D")

ax.set_xlabel("Time (seconds)")
ax.set_ylabel("Random Force (Newtons)")
ax.set_title("Live Random Force vs Time", fontweight="bold")

canvas.draw()  # IMPORTANT: create the renderer once

def update_plot():
    global force_feedback, cpm_text, avg_force_text, pause_warning
    global pause, pause_start

    t = time.time() - start_time
    #random_force = randint(0, 700)
    #below code for testing purposes
    if 2 < t < 5 or 7 < t < 10:
        random_force = 0
    else:
        random_force = randint(0, 700)
    

    # feedback
    if random_force > 500:
        force_feedback = "APPLY LESS FORCE"
    elif 0 < random_force < 400:
        force_feedback = "APPLY MORE FORCE"
    else:
        force_feedback = ""

    # check for long pause between forces (15s)
    if random_force == 0:
        pause = True
        if len(force_y) > 0 and force_y[-1] > 0:
            pause_start = time.time()

    if random_force > 0:
        pause = False
    #change back to 15 
    if pause and (time.time() - pause_start) >= 2:
        pause_warnings.append(f"TOO LONG pause between forces, @time: {round(t, 2)} seconds")
        pause_start = time.time()

    time_x.append(t)
    force_y.append(random_force)

    # maxima + cpm
    indices = find_local_maxima(force_y)
    max_forces = [force_y[i] for i in indices]

    #print instantaneous cpm
    if len(indices) >= 4:
        #find last three intervals using closest local maxes
        three_intervals = [
            time_x[indices[-1]] - time_x[indices[-2]],
            time_x[indices[-2]] - time_x[indices[-3]],
            time_x[indices[-3]] - time_x[indices[-4]],
        ]
        intervals_avg = sum(three_intervals) / 3
        if intervals_avg > 0:
            current_cpm = int(60 / intervals_avg)
            cpm_text = f"Instantaneous cpm is {current_cpm} compressions/min"

    if len(max_forces) >= 1:
        max_force_avg = round(sum(max_forces) / len(max_forces), 2)
        avg_force_text = f"The average maximum force is {max_force_avg} N"

    # sliding time window
    while time_x and (t - time_x[0]) > WINDOW:
        time_x.pop(0)
        force_y.pop(0)

    # update plot
    line.set_data(time_x, force_y)
    ax.set_xlim(max(0, t - WINDOW), t)
    ax.set_ylim(-5, 700)

    canvas.draw()

def mpl_to_pygame_surface():
    """Convert current Matplotlib canvas to a Pygame Surface."""
    w, h = canvas.get_width_height()
    rgba = canvas.buffer_rgba()  # memoryview of RGBA bytes (requires canvas.draw() first)
    return pygame.image.frombuffer(rgba, (w, h), "RGBA")


#Pygame setup 
pygame.init()
font = pygame.font.SysFont("San Francisco", 28)   # default font, size 28

WIN_W, WIN_H = 1000, 700
screen = pygame.display.set_mode((WIN_W, WIN_H))
pygame.display.set_caption("Live Force Graph (Matplotlib inside Pygame)")
clock = pygame.time.Clock()

# update the plot every 200 ms (same as your FuncAnimation interval)
PLOT_UPDATE_MS = 200
accum_ms = 0

running = True
while running:
    dt_ms = clock.tick(60)  # run pygame at up to 60 FPS
    accum_ms += dt_ms

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # update matplotlib data on a timer
    if accum_ms >= PLOT_UPDATE_MS:
        update_plot()
        accum_ms = 0

    # draw pygame background (window)
    screen.fill((173, 216, 230))  # light blue
    pause_surfs = []
    # render text surfaces
    feedback_surf = font.render(force_feedback, True, (200,0,0))
    cpm_surf = font.render(cpm_text, True, (0,0,0))
    avg_surf = font.render(avg_force_text, True, (0,0,0))
    for pause_warning in pause_warnings:
        pause_surfs.append(font.render(pause_warning, True, (0,0,0)))

    # draw them on screen
    screen.blit(feedback_surf, ((WIN_W - feedback_surf.get_width()) / 2, 30))
    screen.blit(avg_surf, ((WIN_W - avg_surf.get_width()) / 2, 60))
    screen.blit(cpm_surf, ((WIN_W - cpm_surf.get_width()) / 2, 90))
    pause_surf_y = 120
    print(pause_surfs)
    for pause_surf in pause_surfs:
        screen.blit(pause_surf, ((WIN_W - pause_surf.get_width()) / 2, pause_surf_y))
        pause_surf_y += 30

    # blit the matplotlib plot into pygame
    plot_surface = mpl_to_pygame_surface()
    screen.blit(plot_surface, (150, 300))

    pygame.display.flip()

pygame.quit()