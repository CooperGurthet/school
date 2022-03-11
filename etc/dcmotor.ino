const int motor = 6;
const int pot = A0;
void setup()
{
    pinMode(motor, OUTPUT);
    pinMode(pot, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        int input = Serial.read();
        if (input == '1')
        {
            digitalWrite(motor, HIGH);
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else if (input == '2')
        {
            digitalWrite(motor, LOW);
            digitalWrite(LED_BUILTIN, LOW);
        }
        // analogWrite(motor, analogRead(pot));
    }
}