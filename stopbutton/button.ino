// https://www.tinkercad.com/things/kWrr4lq1vjW-glorious-esboo/editel?tenant=circuits
// Initialize const variables
// putting const before a variable type makes that variable unchanging
const int buttonPin = 2;
const int green = 8;
const int yellow = 9;
const int red = 10;

// initialize variables
int time = 3000;
int yellowtime = 1000;

void setup()
{
    Serial.begin(9600);      // starts serial port
    pinMode(green, OUTPUT);  // green LED
    pinMode(yellow, OUTPUT); // yellow LED
    pinMode(red, OUTPUT);    // red LED

    // pinMode(buttonPin, INPUT_PULLUP); // button
    /**
     * We can use either INPUT_PULLUP or INPUT
     * If you don't have an external resistor set for the button use INPUT_PULLUP
     */
    pinMode(buttonPin, INPUT); // button
    /**
     * attachInterrupt syntax
     * attachInterrupt(digitalPinToInterrupt(the pin your button is connected to),a function you want to run when the button is pressed, mode)
     * the allowed modes are:
     * - LOW to trigger the interrupt whenever the pin is low,
     * - CHANGE to trigger the interrupt whenever the pin changes value
     * - RISING to trigger when the pin goes from low to high,
     * - FALLING for when the pin goes from high to low.
     * on the arduino uno ONLY pins 2 and 3 can be used for interrupts
     */
    attachInterrupt(digitalPinToInterrupt(buttonPin), Button_pressed, RISING); // runs the button_pressed function when button is pressed

    // starts the loop at red
    digitalWrite(red, HIGH); // turn red LED on
}

void loop()
{

    if (digitalRead(red) == HIGH) // checks if current high led is red
    {
        digitalWrite(red, LOW);    // turn red LED off
        digitalWrite(green, HIGH); // turn green LED on
        Serial.println("Green");
        delay(time);
    }
    else if (digitalRead(green) == HIGH) // checks if current high led is green
    {
        digitalWrite(green, LOW);   // turn green LED off
        digitalWrite(yellow, HIGH); // turn yellow LED on
        Serial.println("Yellow");
        delay(yellowtime);
    }
    else if (digitalRead(yellow) == HIGH) // checks if current high led is yellow
    {
        digitalWrite(yellow, LOW); // turn yellow LED off
        digitalWrite(red, HIGH);   // turn red LED on
        Serial.println("Red");
        delay(time);
    }
}

/**
 * To create a new function you do "type" function_Name(parameters)
 *
 * the type is what you want returned when the function is called
 * use void if you don't change any variables in the function
 *
 * the function name is just like a variable name in that it cant have spaces
 *
 * the parameters are variables that you want to be passed into the function
 * leave empty if your type is void
 *
 * to call a function all you need to do is function_Name(parameters)
 * after the function is ran it will continue back to where it was called
 *
 * setup and loop are special functions
 * the arduino will all the setup function once automatically
 * the arduino will constantly run loop if it is doing nothing else
 */
void Button_pressed() // ran if button is pressed
{
    if (digitalRead(green) == HIGH) // checks if the green LED is on if not do nothing since it is already in a position we want
    {
        digitalWrite(green, LOW);   // turn green LED off
        digitalWrite(yellow, HIGH); // turn yellow LED on
        Serial.println("Yellow");
        delay(yellowtime);
    }
}