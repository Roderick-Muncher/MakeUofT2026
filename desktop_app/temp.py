#App goes here

#code for generating random force
#display spike of force, value of force, force vs time graph on computer screen
#change of peak of force (instantaneous)
#range of force should be 400 to 500 N
#long time of pause between forces like more than 15s than record time where pause happens

import time
from random import randint
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

start_time = time.time()

time_x = []
force_y = []
WINDOW = 10
pause = False
pause_start = 0

fig, ax = plt.subplots()
ax.set_facecolor("#EDE5E8")
line, = ax.plot([], [], color="#D0538D")  # create an empty line

ax.set_xlabel("Time (seconds)")
ax.set_ylabel("Random Force (Newtons)")
ax.set_title("Live Random Force vs Time", fontweight="bold")

def find_local_maxima(data):
    local_max_indices = []
    # A list must have at least 3 elements to have an interior local maximum
    if len(data) < 3:
        return local_max_indices

    # Check internal elements
    for i in range(1, len(data) - 1):
        if data[i-1] < data[i] > data[i+1]:
            local_max_indices.append(i)

    return local_max_indices

# Example Usage:

def update(frame):
    global pause, pause_start
    # current time since start
    t = time.time() - start_time

    # new random value
    random_force = randint(0, 700)
    #below code for testing purposes
    '''if t > 2:
        random_force = 0'''
    if random_force > 500:
        print("Apply less force")
    elif random_force < 400 and random_force > 0:
        print("Apply more force")
    
    #check for long pause between forces (15s)
    if random_force == 0 and force_y[-1] > 0:
        pause = True
        pause_start = time.time()
    if random_force > 0:
        pause = False
    if pause == True and (time.time() - pause_start) >= 15:
        print(f"TOO LONG pause between forces, @time:{round(t, 2)} seconds")

    time_x.append(t)
    force_y.append(random_force)

    #my_list = [1, 3, 2, 4, 3, 5, 4, 6, 5]
    indices = find_local_maxima(force_y)
    max_forces = [force_y[i] for i in indices]
    #print instantaneous cpm
    if len(indices) >= 4:
        #find last three intervals using closest local maxes
        three_intervals = [time_x[indices[-1]] - time_x[indices[-2]], time_x[indices[-2]] - time_x[indices[-3]], time_x[indices[-3]] - time_x[indices[-4]]]
        intervals_avg = sum(three_intervals) / 3
        current_cpm = int(60 / intervals_avg)
        print(f"Instantaneous cpm is {current_cpm} compressions/min")
    
    if len(max_forces) >= 1:
        max_force_avg = round((sum(max_forces) / len(max_forces)), 2) 
        print(f"The average maximum force is {max_force_avg}")


    while time_x and (t-time_x[0]) > WINDOW:
        time_x.pop(0)
        force_y.pop(0)

    # update line data
    line.set_data(time_x, force_y)

    ax.set_xlim(max(0, t - WINDOW), t)  # sliding window
    ax.set_ylim(-5, 700) 

    return line,

ani = FuncAnimation(fig, update, interval=200)  # update every 200 ms
plt.show()

'''import time
import random
import pygame

import matplotlib
matplotlib.use("Agg")  # draw off-screen (no Matplotlib window)
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas

# ---------- Matplotlib setup (off-screen) ----------
fig = Figure(figsize=(6, 4), dpi=100)   # 600x400 image
canvas = FigureCanvas(fig)
ax = fig.add_subplot(111)

ax.set_title("Live Random Data vs Time", fontweight="bold")
ax.set_xlabel("Time (s)")
ax.set_ylabel("Value")

x_data, y_data = [], []
(line,) = ax.plot([], [])  # keep a reference to the line

start_time = time.time()

def update_plot():
    """Update data and redraw the Matplotlib figure to its canvas."""
    global pause, pause_start
    # current time since start
    t = time.time() - start_time

    # new random value
    random_force = randint(0, 700)
    #below code for testing purposes
    #if t > 2:
        #random_force = 0
    if random_force > 500:
        print("Apply less force")
    elif random_force < 400 and random_force > 0:
        print("Apply more force")
    
    #check for long pause between forces (15s)
    if random_force == 0 and force_y[-1] > 0:
        pause = True
        pause_start = time.time()
    if random_force > 0:
        pause = False
    if pause == True and (time.time() - pause_start) >= 15:
        print(f"TOO LONG pause between forces, @time:{round(t, 2)} seconds")

    time_x.append(t)
    force_y.append(random_force)

    #my_list = [1, 3, 2, 4, 3, 5, 4, 6, 5]
    indices = find_local_maxima(force_y)
    max_forces = [force_y[i] for i in indices]
    #print instantaneous cpm
    if len(indices) >= 4:
        #find last three intervals using closest local maxes
        three_intervals = [time_x[indices[-1]] - time_x[indices[-2]], time_x[indices[-2]] - time_x[indices[-3]], time_x[indices[-3]] - time_x[indices[-4]]]
        intervals_avg = sum(three_intervals) / 3
        current_cpm = int(60 / intervals_avg)
        print(f"Instantaneous cpm is {current_cpm} compressions/min")
    
    if len(max_forces) >= 1:
        max_force_avg = round((sum(max_forces) / len(max_forces)), 2) 
        print(f"The average maximum force is {max_force_avg}")


    while time_x and (t-time_x[0]) > WINDOW:
        time_x.pop(0)
        force_y.pop(0)

    # update line data
    line.set_data(time_x, force_y)

    ax.set_xlim(max(0, t - WINDOW), t)  # sliding window
    ax.set_ylim(-5, 700) 

    return line,

    canvas.draw()  # render to the Agg buffer

def mpl_to_pygame_surface():
    # Ensure renderer exists
    canvas.draw()

    w, h = canvas.get_width_height()
    rgba = canvas.buffer_rgba()   # memoryview of RGBA bytes
    return pygame.image.frombuffer(rgba, (w, h), "RGBA")


# ---------- Pygame setup ----------
pygame.init()
WINDOW_W, WINDOW_H = 800, 600
screen = pygame.display.set_mode((WINDOW_W, WINDOW_H))
pygame.display.set_caption("Matplotlib Live Graph in Pygame")

clock = pygame.time.Clock()
running = True

# optional: control update rate of the plot separately
PLOT_UPDATE_MS = 200
last_plot_update = 0

while running:
    dt_ms = clock.tick(60)  # cap at 60 FPS
    last_plot_update += dt_ms

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Update plot every PLOT_UPDATE_MS (not every frame)
    if last_plot_update >= PLOT_UPDATE_MS:
        update_plot()
        last_plot_update = 0

    # Draw everything
    screen.fill((173, 216, 230))  # window background
    plot_surface = mpl_to_pygame_surface()
    screen.blit(plot_surface, (100, 100))  # position on the pygame window

    pygame.display.flip()

pygame.quit()'''