// libraries
#include <IRremote.h> //Library for remote

// constants
#define listsize 3                           //# of elements in the code list
#define maxDistance 100                      // upper range of distances to active LED
#define mid2highDistance maxDistance / 3 * 2 // upper middle range of distances to active LED
#define mid2lowDistance maxDistance / 3      // lower middle range of distances to active LED
#define minDistance 0                        // lower range of distances to active LED

// button codes:
// custom remote command
#define benter 11
#define breset 15
#define bnew 19

// School remote commands
// #define benter 25
// #define breset 13
// #define bnew 21

// pins
const int IR_RECEIVE_PIN = 7;
const int sensor = 12;
const int buzzer = 5;
const int echoPin = 8;
const int trigPin = 6;

// LED pins
const int PIN_RED = 9;
const int PIN_GREEN = 10;
const int PIN_BLUE = 11;

// passcode
int code[] = {12, 13, 14};

// variables
int inputs[listsize]; // list to hold inputed codes
int i = 0;            // variable to store code index
int state = LOW;      // by default, no motion detected
int sensorpower = 1;  // variable to store if sensor should be on or off

void setup()
{
    //  begin processes
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN);
    // set pinmodes
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(sensor, INPUT);
}

void loop()
{
    sense();  // check if pir is active
    remote(); // check for any remote inputs
}

bool listequal(int list1[listsize], int list2[listsize]) // Function to check if lists are equal
{

    for (int i = 0; i < listsize; i++) // increments until end of list
    {
        // Serial.println(list1[i]);
        // Serial.println(list2[i]);
        if (list1[i] != list2[i]) // Checks if this index is equal
            return false;         // if any of them aren't equal its not equal
    }
    return true; // if the for loop completes then they are equal
}

void sense()
{
    int val = digitalRead(sensor);           // read sensor value
    if ((val == HIGH) && (sensorpower == 1)) // check if the sensor is HIGH and if the alarm system is on
    {
        distanceSense(); // checks distance from the board
        delay(50);       // delay 50 milliseconds

        if (state == LOW) // place things that should only be done once per movement here
        {
            Serial.println("Motion detected!");
            state = HIGH; // update variable state to HIGH
        }
    }
    else
    {
        digitalWrite(buzzer, LOW); // turns buzzer off
        delay(50);                 // delay 50 milliseconds

        if (state == HIGH) // place things that should only be done once per movement here
        {
            setColor(0, 0, 0); // turns led off
            state = LOW;       // update variable state to LOW
            Serial.println("Motion stopped!");
        }
    }
}

void remote()
{
    if (IrReceiver.decode()) // check if the reveiver is working and if there is data in buffer
    {
        if (IrReceiver.decodedIRData.flags != 1) // checks if the pin is repeated (stops multiple inputs from one button press)
        {
            uint32_t command = IrReceiver.decodedIRData.command; // Gets the data from
            switch (command)
            {                                      // Checks what button was pressed
            case breset:                           // sreset
                memset(inputs, 0, sizeof(inputs)); // resets the inputed code
                i = 0;                             // resets incrementer
                break;                             // exits switch case
            case bnew:                             // custom code
                if (sensorpower != 0)              // if the alarm is not off then break
                    break;                         // exits switch case
                for (int i = 0; i < listsize; i++) // increments until end of list
                {
                    code[i] = inputs[i]; // replaces the code list with the number inputed
                }
                memset(inputs, 0, sizeof(inputs)); // resets the inputed code
                break;                             // exits switch case
            case benter:                           // Enter
                if (listequal(inputs, code))       // Checks if inputed code is equal to passcode
                {
                    Serial.println("correct code");
                    sensorpower = 0; // turns off the alarm system
                }
                else
                {
                    Serial.println("wrong code");
                    sensorpower = 1; // turns on the alarm system
                }
                memset(inputs, 0, sizeof(inputs)); // resets the inputed code
                i = 0;                             // resets incrementer
                break;                             // exits switch case
            default:                               // if no other cases activate
                inputs[i] = command;               // sets the list at index i to current button press
                i++;                               // increments the index counter
                break;                             // exits switch case
            }
        }
        IrReceiver.resume(); // gets next button from the IR
    }
}

void distanceSense()
{
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    int duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // distance in cm
    if (distance < maxDistance) // is in range of distances to active LED
    {
        digitalWrite(buzzer, HIGH);                                    // turns buzzer on
        if ((distance > minDistance) && (distance <= mid2lowDistance)) // red
        {
            int color = map(distance, minDistance, mid2lowDistance, 255, 0); // map the distance to 0-255(rgb max colors) to get brightness corresponding to distance as well as color
            setColor(255, 0, 0);                                             // sets the color of the LED
            // setColor(color, 0, 0);                                       // sets the color of the LED
            return; // ends this function immediately
        }
        else if ((distance > mid2lowDistance) && (distance <= mid2highDistance)) // blue
        {
            int color = map(distance, mid2lowDistance, mid2highDistance, 255, 0); // map the distance to 0-255(rgb max colors) to get brightness corresponding to distance as well as color
            setColor(0, 0, color);                                                // sets the color of the LED
            return;                                                               // ends this function immediately
        }
        else if (distance > mid2highDistance) // green
        {
            int color = map(distance, minDistance, maxDistance, 255, 0); // map the distance to 0-255(rgb max colors) to get brightness corresponding to distance as well as color
            setColor(0, color, 0);                                       // sets the color of the LED
            return;                                                      // ends this function immediately
        }
    }
    return; // ends this function immediately
}

void setColor(int R, int G, int B) // simple function to set the color of rgbLED given 3 values R,G,B
{
    analogWrite(PIN_RED, R);
    analogWrite(PIN_GREEN, G);
    analogWrite(PIN_BLUE, B);
}