/************************************

http://arduino.cc/en/Reference/HomePage

http://playground.arduino.cc/Interfacing/Csharp
http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging

*/

#include "fArduino.h"

#define ON_BOARD_LED 13
boolean _ledState = false;
int _counter = 0;

void setup() {

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Serial Communicator");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
}

void PowerLed(boolean state) {

    Board.LedOn(ON_BOARD_LED, state);
}

void loop() {

    
    Board.LedOn(ON_BOARD_LED, _ledState);
    Board.Delay(100);
    _counter++;

    if (_counter % 30 == 0) {

        Board.Trace(Board.Format("counter:%d", _counter));
    }

    if (Serial.available()) {

        while (Serial.available()) {

            boolean executed = false;
            String s         = Serial.readStringUntil('\n');

            if (s == "reset") {
                _counter = 0;
                executed = true;
            }
            else if (s == "led") {
                _ledState = !_ledState;
                executed = true;
            }
            if (executed) {
                Board.Trace(Board.Format("[%s executed]", s.c_str()));
            }
            else {
                Board.Trace(Board.Format("[Invalid command:%s]", s.c_str()));
            }
        }
    }
}

