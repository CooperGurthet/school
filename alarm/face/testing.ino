/**
 *@file testing.ino
 *@date 2022 - 02 - 23
 */

// Libraries
#include <Servo.h>
// Initialize const variables
const int verticalpin = 5;
const int horizontalpin = 6;
// Initialize variables
Servo servoVer; // Vertical Servo
Servo servoHor; // Horizontal Servo

int x;
int y;
int prevX;
int prevY;

void setup()
{
    Serial.begin(9600);
    servoVer.attach(verticalpin);   // Attach Vertical Servo to Pin 5
    servoHor.attach(horizontalpin); // Attach Horizontal Servo to Pin 6
    // servoVer.write(90);             // set motor to midpoint
    // servoHor.write(90); // set motor to midpoint
}
void loop()
{
    // servoVer.write(140);
    // delay(1000);
    // servoVer.write(250);
    // delay(1000);

    // servoVer.write(210);
    // delay(500);
    // servoVer.write(200);
    // delay(500);
    // servoVer.write(190);
    // delay(500);
    // servoVer.write(190);
    // delay(500);
    Serial.println(servoVer.read());
}