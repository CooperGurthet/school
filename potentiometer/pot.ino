/**
 *@file pot.ino
 *@date 2022 - 02 - 07
 */

// Libraries

// Initialize const variables
const int LED = 9;
const int potentiometer = A1;
// Initialize variables

void setup()
{
    Serial.begin(9600);
    pinMode(potentiometer, INPUT);
    pinMode(LED, OUTPUT);
}

void loop()
{
    int input = analogRead(potentiometer);
    int converted = map(input, 0, 1023, 0, 255);
    Serial.print("intiial input: ");
    Serial.println(input);
    Serial.print("mapped input: ");
    Serial.println(converted);
    // Serial.print(input);
    // Serial.print("\t");
    // Serial.println(converted);
    analogWrite(LED, converted);
}