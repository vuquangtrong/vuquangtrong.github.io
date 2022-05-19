#!/usr/bin/python

import RPi.GPIO as GPIO
import time, subprocess, signal, os

# first message
subprocess.Popen('/home/pi/base/start')

# use BCM mode, see low level pin number
GPIO.setmode(GPIO.BCM)

# BCM 24  = BOARD 18
# Pull down to make it GND by default
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

count = 0

try:

    while True:
        time.sleep(1)
        button = GPIO.input(24)
        print("Button: ", button)

        if button == 1:
            count += 1
            if count == 3:
                p =  subprocess.Popen(['ps', '-A'], stdout=subprocess.PIPE)
                out, err = p.communicate()
                for line in out.splitlines():
                    #print(line)
                    if (b'local_rtk' in line) or (b'str2str' in line):
                        pid = int(line.split(None, 1)[0])
                        os.kill(pid, signal.SIGKILL)
                # run new
                time.sleep(1)
                subprocess.Popen('/home/pi/base/local_rtk')
        else:
            count = 0

except KeyboardInterrupt:
    print("Exit")

GPIO.cleanup()

