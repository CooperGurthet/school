# @file gui.py
# @date 2022 - 02 - 08

# Libraries
# @file input.py
# @date 2022 - 01 - 13


# Libraries
import tkinter as Tk
import serial.tools.list_ports
from datetime import datetime
from PIL import Image, ImageTk
import os

from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume

devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(
    IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = cast(interface, POINTER(IAudioEndpointVolume))

serBuffer = ""  # start with empty buffer

path = os.path.dirname(__file__)
filename = path+'\\images\\rotate_dial.png'


def map_range(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min


def connect():
    comport = clicked.get()  # gets current selected port
    # checks if the com ports are unavailable

    if ((comport == 'Com Ports') or (comport == 'No Available Com Ports')):
        return
    comport = comport.split(' ')[0]
    # turns off the original window
    connector.destroy()

    # creates new window
    backgroundcolor = 'white'
    root = Tk.Tk()
    root.geometry("400x250+-10+0")
    root.attributes("-topmost", True)
    root.config(bg=backgroundcolor)

    # connects to the serial port of the comport selected
    serialPort = comport
    baudRate = 9600
    ser = serial.Serial(serialPort, baudRate, timeout=0,
                        writeTimeout=0)  # ensure non-blocking

    # create the output text
    Output = Tk.Label(root, height=5, width=15)

    # image holder
    image = Image.open(filename)
    width, height = image.size
    image.thumbnail((width/5, height/5))
    image = image.rotate(135)  # offsets the image to be correct
    photoimage = ImageTk.PhotoImage(image)
    image_label = Tk.Label(root, image=photoimage, bg=backgroundcolor)

    # Packs all the tkinter widgets
    Output.pack()
    image_label.pack()
    # Add image to the Canvas Items

    def rotate_image(degrees):
        degrees = map_range(degrees, 0, 100, 0, 280)
        new_image = image.rotate(-int(degrees))
        photoimage = ImageTk.PhotoImage(new_image)
        image_label.image = photoimage  # Prevent garbage collection
        image_label.config(image=photoimage)

    def changevolume(input):
        input = int(input)
        volume.SetMasterVolumeLevelScalar(
            (input/100), None)  # changes system volume
        rotate_image(input)

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
                changevolume(serBuffer)

                # gets current time in HH:MM:SS format
                timenow = datetime.now()
                curtime = str(timenow.hour)+':'+str(timenow.minute) + \
                    ':'+str(timenow.second)

                # sets the output text to the time + buffer
                formated = curtime+": "+serBuffer+"%"
                # replaces current text in output with new text
                Output['text'] = formated
                serBuffer = ""  # empty the buffer
            else:
                serBuffer += content  # add to the buffer

        root.after(10, readSerial)  # check serial again soon

    root.after(100, readSerial)  # check serial

    root.mainloop()  # run loop until window closes
    ser.close()  # closes the serial port


# creates initial tkinter window
connector = Tk.Tk()
connector.geometry("250x100+-10+0")
connector.attributes("-topmost", True)


def refresh():
    ports = (list(serial.tools.list_ports.comports()))  # gets list of ports
    if ports == []:  # checks if there are no ports
        # "populate" the ports list so no error on no com ports
        ports = ["No Available Com Ports"]
    # sets the words on the dropdown box as "Com Ports"
    clicked.set("Com Ports")
    return ports  # returns the ports list in the call of function


# Create Title
connectTitle = Tk.Label(
    connector, text="Connect to com ports")
connectTitle.config(font=("Courier", 14))

# create button to connect
connectbtn = Tk.Button(connector, text="connect", command=connect)

# create a button to refresh ports
refreshbtn = Tk.Button(connector, text="refresh", command=refresh)

# creates a menu to select com ports
clicked = Tk.StringVar()
clicked.set("Com Ports")
ports = refresh()
menu = Tk.OptionMenu(connector, clicked, *ports)

# packs the widgetss
connectTitle.pack(side=Tk.TOP)
menu.pack()
refreshbtn.pack(side=Tk.LEFT)
connectbtn.pack(side=Tk.RIGHT)

connector.mainloop()  # loops this window until closed
