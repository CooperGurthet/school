/**
 *
 * when the user enters ‘1’ all lights turn on
 * when the user enters ‘2’ all lights flash
 * when the user enters ‘3’ lights cycle repeatedly
 * when the user enters ‘q’ or ‘e’ the lights turn off
 * when + or - is pressed the speed of the LED increase or decrease
 *
 */

// Libraries

// Initialize const variables
#define green 13  // green pin
#define yellow 12 // yellow pin
#define red 11    // red pin
// Initialize variables
String input;
int time = 500;
int flag;
// flags

void setup()
{
    Serial.begin(9600);
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(red, OUTPUT);
    delay(2000);
    Serial.println("Type Command");
}
void loop()
{
    if (Serial.available())
    {
        input = Serial.readStringUntil('\n'); // gets input until newline
        input.trim();                         // trims the extra bits off input

        if (input.equals("1"))
        {
            allOn();
        }
        else if (input.equals("2"))
        {
            flash();
        }
        else if (input.equals("3"))
        {
            cycle();
        }
        else if (input.equals("q") || input.equals("e"))
        {
            stop();
        }
        else if (input.equals("+"))
        {
            speedUp();
        }
        else if (input.equals("-"))
        {
            slowDown();
        }
        Serial.print("Command: ");
        Serial.println(input);
    }
}
void allOn()
{
    digitalWrite(green, HIGH);  // turns on green
    digitalWrite(yellow, HIGH); // turns on yellow
    digitalWrite(red, HIGH);    // turns on red
}
void flash()
{
    digitalWrite(green, HIGH);  // turns on green
    digitalWrite(yellow, HIGH); // turns on yellow
    digitalWrite(red, HIGH);    // turns on red
    delay(time);

    digitalWrite(green, LOW);  // turns off green
    digitalWrite(yellow, LOW); // turns off yellow
    digitalWrite(red, LOW);    // turns off red

    flag = Serial.peek(); // reads start of serial
    if (flag == -1)       // checks if serial is nothing if so loop
    {
        flash(); // loops
    }
}
void cycle()
{
    digitalWrite(green, HIGH); // turns on green
    delay(time);
    digitalWrite(green, LOW);   // turns off green
    digitalWrite(yellow, HIGH); // turns on yellow
    delay(time);
    digitalWrite(yellow, LOW); // turns off yellow
    digitalWrite(red, HIGH);   // turns on red
    delay(time);
    digitalWrite(red, LOW); // turns off red
    flag = Serial.peek();   // reads start of serial
    if (flag == -1)         // checks if serial is nothing if so loop
    {
        cycle(); // loops
    }
}
void stop()
{
    digitalWrite(green, LOW);  // turns off green
    digitalWrite(yellow, LOW); // turns off yellow
    digitalWrite(red, LOW);    // turns off red
}
void speedUp()
{
    time = time - 100;
}
void slowDown()
{
    time = time + 100;
}
void reset()
{
}