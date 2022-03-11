# @file input.py
# @date 2022 - 01 - 13


# Libraries
import tkinter as Tk
import serial
from datetime import datetime

root = Tk.Tk()
root.geometry("500x500+-10+0")
root.attributes("-topmost", True)

serialPort = "COM8"
baudRate = 9600
ser = serial.Serial(serialPort, baudRate, timeout=0,
                    writeTimeout=0)  # ensure non-blocking


def Sendserial():
    inpdata = str.lower(input.get(1.0, "end"))
    inpbyte = bytes(inpdata, 'utf-8')
    ser.write(inpbyte)


serBuffer = ""

# create the input text
input = Tk.Text(root, height=5, width=52)

# create the output text
Output = Tk.Label(root, height=5, width=52)


# Create label
Title = Tk.Label(
    root, text="1 turns on all lights\n2 blinks all lights\n3 cycles on all lights\nq or e turns off lights\n+ increases speed\n- decreases speed")
Title.config(font=("Courier", 14))

# create button to send
Send = Tk.Button(root, text="Send", command=Sendserial)

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
