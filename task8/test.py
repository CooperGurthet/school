# @file input.py
# @date 2022 - 01 - 13


# Libraries
import tkinter as Tk
import serial
import serial.tools.list_ports
from datetime import datetime


def connect():
    comport = clicked.get()  # gets current selected port
    # checks if the com ports are unavailable
    if ((comport == 'Com Ports') or (comport == 'No Available Com Ports')):
        return
    # turns off the original window
    connector.destroy()

    # creates new window
    root = Tk.Tk()
    root.geometry("500x500+-10+0")
    root.attributes("-topmost", True)

    # connects to the serial port of the comport selected
    serialPort = comport
    baudRate = 9600
    ser = serial.Serial(serialPort, baudRate, timeout=0,
                        writeTimeout=0)  # ensure non-blocking

    def Sendserial():  # sends the data to the serial port
        # turns the input text into lower case
        inpdata = str.lower(input.get(1.0, "end"))
        inpbyte = bytes(inpdata, 'utf-8')  # turns the string into bytes
        ser.write(inpbyte)  # sends the bytes to the serial monitor

    serBuffer = ""  # start with empty buffer

    # create the input text box
    input = Tk.Text(root, height=5, width=52)

    # create the output text
    Output = Tk.Label(root, height=5, width=52)

    # Create Title
    Title = Tk.Label(
        root, text="1 turns on all lights\n2 blinks all lights\n3 cycles on all lights\nq or e turns off lights\n+ increases speed\n- decreases speed")
    Title.config(font=("Courier", 14))

    # create button to send text
    Send = Tk.Button(root, text="Send", command=Sendserial)

    # Packs all the tkinter widgets
    Title.pack(side=Tk.TOP)
    input.pack()
    Send.pack()
    Output.pack()

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
                serBuffer += "\n"  # add the newline to the buffer

                # gets current time in HH:MM:SS format
                timenow = datetime.now()
                curtime = str(timenow.hour)+':'+str(timenow.minute) + \
                    ':'+str(timenow.second)

                formated = curtime+": "+serBuffer  # sets the output text to the time + buffer
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


# Create Titile
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
