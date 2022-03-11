# @file face.py
# @date 2022 - 02 - 22

# Libraries
import cv2
import serial

port = 'COM5'
baudrate = 9600
arduino = serial.Serial(port, baudrate)
print('connected to Arduino')
# Load the cascade
eye_cascade = cv2.CascadeClassifier('house\\face\\haarcascade_eye.xml')
# face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')


def findEyes():
    # To capture video from webcam.
    cap = cv2.VideoCapture(0)

    while True:
        # Read the frame
        _, img = cap.read()
        img = cv2.flip(img, 1)

        # Convert to grayscale
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # Detect the faces
        eyes = eye_cascade.detectMultiScale(gray, 1.1, 4)

        # Draw the rectangle around each face
        for (x, y, w, h) in eyes:
            cv2.rectangle(img, (x, y), (x + w, y + h), (255, 255, 255), 2)
            arr = {y: y+h, x: x+w}

            print(arr)
            print('X :' + str(x))
            print('Y :'+str(y))
            print('x+w :' + str(x+w))
            print('y+h :' + str(y+h))

            # Center of roi (Rectangle)
            xx = int((x+(x+h))/2)
            yy = int((y+(y+w))/2)
            print(xx)
            print(yy)
            center = (xx, yy)

            # sending data to arduino
            print("Center of Rectangle is :", center)
            data = "X{0:d}Y{1:d}Z".format(xx, yy)
            print("output = '" + data + "'")
            arduino.write(bytes(data, 'UTF-8'))

        # Display
        cv2.imshow('img', img)

        # Stop if escape key is pressed
        k = cv2.waitKey(30) & 0xff
        if k == 27:
            break

    # Release the VideoCapture object
    cap.release()

# if motion detected turn on the face tracker?


if __name__ == '__main__':
    findEyes()
