// Libraries
#include <Thread.h>
#include <StaticThreadController.h>

// Threads
Thread name = Thread();
Thread myThread = Thread();
Thread newerThread = Thread();
StaticThreadController<3> controll(&myThread, &name, &newerThread);

// Pins
int ledPin = 13;

// callback for myThread
void niceCallback()
{
    bool power = digitalRead(ledPin);
    digitalWrite(ledPin, !power);
}
void NamedCallback()
{
    Serial.println("test");
}
void doubleup()
{
    Serial.println("###############################");
}

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    name.onRun(NamedCallback);
    name.setInterval(250);

    myThread.onRun(niceCallback);
    myThread.setInterval(500);

    newerThread.onRun(doubleup);
    newerThread.setInterval(500);
}

void loop()
{
    controll.run();

    // Other code...
    int x = 0;
    x = 1 + 2;
}