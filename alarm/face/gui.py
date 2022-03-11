# @file gui.py
# @date 2022 - 02 - 23

# Libraries
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

serBuffer = ""  # start with empty buffer


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

    # Packs all the tkinter widgets
    Output.pack()

    def send(center, xx, yy):
        # sending data to arduino
        print("Center of Rectangle is :", center)
        data = "X{0:d}Y{1:d}Z".format(xx, yy)
        print("output = '" + data + "'")
        ser.write(data)

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
                send()

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
