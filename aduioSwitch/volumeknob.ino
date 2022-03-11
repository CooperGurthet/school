/**
 *@file volumeknob.ino
 *@date 2022 - 02 - 08
 */

// Libraries

// Initialize const variables
const int potentiometer = A1;
// Initialize variables

void setup()
{
    Serial.begin(9600);
    pinMode(potentiometer, INPUT);
}

void loop()
{
    int converted = map(analogRead(potentiometer), 0, 1023, 0, 100);
    Serial.println(converted);
    delay(500);
}