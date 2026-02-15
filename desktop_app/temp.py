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
pause_start = 0.0

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
    global pause, pause_start

    t = time.time() - start_time
    random_force = randint(0, 700)
    #below code for testing purposes
    '''if t > 2:
        random_force = 0'''

    # feedback
    if random_force > 500:
        print("Apply less force")
    elif 0 < random_force < 400:
        print("Apply more force")

    # check for long pause between forces (15s)
    if random_force == 0 and len(force_y) > 0 and force_y[-1] > 0:
        pause = True
        pause_start = time.time()

    if random_force > 0:
        pause = False

    if pause and (time.time() - pause_start) >= 15:
        print(f"TOO LONG pause between forces, @time:{round(t, 2)} seconds")

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
            print(f"Instantaneous cpm is {current_cpm} compressions/min")

    if len(max_forces) >= 1:
        max_force_avg = round(sum(max_forces) / len(max_forces), 2)
        print(f"The average maximum force is {max_force_avg}")

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

    # blit the matplotlib plot into pygame
    plot_surface = mpl_to_pygame_surface()
    screen.blit(plot_surface, (150, 150))

    pygame.display.flip()

pygame.quit()