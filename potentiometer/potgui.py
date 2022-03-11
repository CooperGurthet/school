# @file potgui.py
# @date 2022 - 02 - 07

# Libraries
# @file stoplightui.py
# @date 2022 - 01 - 11

# TODO: add time
# TODO: change window color to current color

# Libraries
import tkinter as Tk
import serial
from datetime import datetime
import time

color = '#ffffff'

serialPort = "COM5"
baudRate = 9600
ser = serial.Serial(serialPort, baudRate, timeout=0,
                    writeTimeout=0)  # ensure non-blocking

root = Tk.Tk()
root.geometry("200x250+-10+0")
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


def rgb_to_hex(rgb):
    r, g, b = rgb
    return '#%02x%02x%02x' % (r, g, b)


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
            buffer = serBuffer.split('\t')
            initial = ((buffer[0]))
            converted = int((buffer[1].strip()))
            hex = rgb_to_hex((0, converted, 0))

            Box['bg'] = hex

            serBuffer += "\n"  # add the newline to the buffer
            timenow = datetime.now()
            curtime = str(timenow.hour)+':'+str(timenow.minute) + \
                ':'+str(timenow.second)
            formated = curtime+":\n Initial value: " + \
                str(initial)+"\n Mapped value: " + str(converted)
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
