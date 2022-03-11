/**
 *@file stoplight.ino
 *@date 2022 - 01 - 12
 */
// Libraries

// Initialize const variables
const int green = 10; // green pin
const int yellow = 9; // yellow pin
const int red = 8;    // red pin
// Initialize variables
int green_blink_time = 500; // period for one blink of green led
int green_time = 5000;      // time that solid green led is on
int yellow_time = 1000;     // time yellow led is on
int red_time = 3000;        // time red led is on
void setup()
{
    Serial.begin(9600);
    pinMode(green, OUTPUT);  // initializes green led
    pinMode(yellow, OUTPUT); // initializes yellow led
    pinMode(red, OUTPUT);    // initializes red led
}

void loop()
{
    digitalWrite(red, LOW); // turns off red

    Serial.println("Advanced Green");
    for (int i = 0; i < 3; i++) // loops blink 3 times
    {
        digitalWrite(green, HIGH); // turns on green
        delay(green_blink_time);   // waits specified time
        digitalWrite(green, LOW);  // turns off green
        delay(green_blink_time);   // waits specified time
    }
    Serial.println("Green");
    digitalWrite(green, HIGH); // turns on green
    delay(green_time);         // waits specified time

    Serial.println("Yellow");
    digitalWrite(green, LOW);   // turns off green
    digitalWrite(yellow, HIGH); // turns on yellow
    delay(yellow_time);         // waits specified time

    Serial.println("Red");
    digitalWrite(yellow, LOW); // turns off yellow
    digitalWrite(red, HIGH);   // turns on red
    delay(red_time);           // waits specified time
}