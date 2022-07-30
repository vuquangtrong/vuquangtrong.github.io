import io
import time
import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.animation
import serial

from fs9922_dmm4 import parse

PLOT_LIMIT = 60
y_min = -1
y_max =  1

fig, ax = plt.subplots(1, 1, figsize=(10,8))
ax.set_title("Digital Multimeter")
ax.set_xlabel("second")
ax.set_ylabel("value")
ax.set_ylim([y_min, y_max])


##########
def static_vars(**kwargs):
    def decorate(func):
        for k in kwargs:
            setattr(func, k, kwargs[k])
        return func
    return decorate


##########
def get_data(line):
    return parse(line)


##########
@static_vars(counter=0)
def animate(i, xs, ys, serial, limit=PLOT_LIMIT):
    global y_min
    global y_max
    
    # grab the data
    try:
        # next second
        animate.counter += 1
        line = serial.readline()
        data = get_data(line)

        if data < y_min:
            y_min = data - 0.5
        if data > y_max:
            y_max = data + 0.5
        
        # Add x and y to lists
        xs.append(animate.counter)
        ys.append(data)
        
        # Trim xs, ys
        xs = xs[-limit:]
        ys = ys[-limit:]
    
    except ValueError:
        print(f"W: {time.time()} :: EXCEPTION!")
    
    else:
        # Draw x and y lists
        ax.clear()
        ax.set_ylim([y_min, y_max])
        ax.plot(xs, ys)

##########
if __name__ == '__main__':
    # open and read
    with serial.Serial('COM5', 2400) as dmm:
        anim = mpl.animation.FuncAnimation(fig, animate, fargs=([None], [None], dmm))
        plt.show()
        plt.close()
