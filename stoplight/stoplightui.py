# @file stoplightui.py
# @date 2022 - 01 - 11

# TODO: add time
# TODO: change window color to current color

# Libraries
import tkinter as Tk
import serial
from datetime import datetime
import time

color = '#4a7abc'

serialPort = "COM5"
baudRate = 9600
ser = serial.Serial(serialPort, baudRate, timeout=0,
                    writeTimeout=0)  # ensure non-blocking

root = Tk.Tk()
root.geometry("200x200+-10+0")
root.attributes("-topmost", True)

serBuffer = ""

# create the output text
Output = Tk.Label(root, height=5, width=52)

# Create label
Title = Tk.Label(root, text="Current Color:")
Title.config(font=("Courier", 14))

# box
Box = Tk.Label(root, height=9, width=18, bg=color)


Title.pack(side=Tk.TOP)
Box.pack()
Output.pack(side=Tk.BOTTOM)


def colorChange(buffer):
    i = 0
    buffer = str.upper(buffer)
    if buffer == 'ADVANCED GREEN':  # doesn't work
        if i < 3:  # loops blink 3 times
            Box['bg'] = '#008000'
            time.sleep(0.5)
            Box['bg'] = '#FFFFFF'
            time.sleep(0.5)
            i = i+1

    elif buffer == 'GREEN':
        Box['bg'] = '#008000'  # sets the color of box to green
    elif buffer == 'YELLOW':
        Box['bg'] = '#ffff00'  # sets the color of box to
    elif buffer == 'RED':
        Box['bg'] = '#ff0000'  # sets the color of box to


def readSerial():
    while True:
        content = ser.read().decode("ascii")  # attempt to read a character from Serial

        # was anything read?
        if len(content) == 0:
            break

        # get the buffer from outside of this function
        global serBuffer

        # check if character is a delimeter
        if content == '\r':
            content = ''  # don't want returns. chuck it

        if content == '\n':
            colorChange(serBuffer)
            serBuffer += "\n"  # add the newline to the buffer
            timenow = datetime.now()
            curtime = str(timenow.hour)+':'+str(timenow.minute) + \
                ':'+str(timenow.second)
            formated = curtime+": "+serBuffer
            Output['text'] = formated
            # T.insert(Tk.END, formated)
            serBuffer = ""  # empty the buffer
        else:
            serBuffer += content  # add to the buffer

    root.after(10, readSerial)  # check serial again soon


root.after(100, readSerial)

root.mainloop()
ser.close()


def find_USB_device():
    myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
    print(myports)
    usb_port_list = [p[0] for p in myports]

    return usb_port_list
