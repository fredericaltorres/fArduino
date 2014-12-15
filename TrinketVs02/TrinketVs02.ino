/*
    http://arduino.cc/en/Reference/HomePage
    https://learn.adafruit.com/introducing-trinket/pinouts

    Torres Frederic 2014.12.10
*/

int redBoardled = 1; // blink 'digital' pin 1 - AKA the built in red LED
int extled      = 0; 

void LedOn(int pin, boolean state) {

    digitalWrite(pin, state ? HIGH : LOW);
}

void CurrentOn(int pin, boolean state) {

    analogWrite(pin, state ? HIGH : LOW);
}

// Return how many milli second we must wait
// Loop between 0 and 300 infinitely
int GetNextWaitTime() {
    
    static int Max = 30;
    static int i = 0;
    if (i >= Max)
        i = 0;
    i++;
    return i * 10;
}

void setup() {
    
    pinMode(redBoardled, OUTPUT);
    pinMode(extled,      OUTPUT);
}

void loop() { 

    int waitTime = GetNextWaitTime();

    LedOn(redBoardled, true); // One led on
    CurrentOn(extled, !true); // One led off

    delay(waitTime);

    LedOn(redBoardled, false); // One led off
    CurrentOn(extled, !false); // One led on

    delay(waitTime*2); // Wait twice the time
}
