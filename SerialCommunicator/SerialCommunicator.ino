/************************************

http://arduino.cc/en/Reference/HomePage

http://playground.arduino.cc/Interfacing/Csharp
http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging

TV for $1 - https://www.youtube.com/watch?v=WlBXiZpuncg

*/


#include "fArduino.h"

#define ON_BOARD_LED 13
boolean _ledState = false;
int _counter      = 0;
int eeprom_counter_addr;

void setup() {

    // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole
    Board.Delay(1000);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Serial Communicator With EEPROM");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);

    eeprom_counter_addr = EEPROM.getAddress(sizeof(int));
}

void PowerLed(boolean state) {

    Board.LedOn(ON_BOARD_LED, state);
}

void loop() {
    
    Board.LedOn(ON_BOARD_LED, _ledState);
    Board.Delay(100);
    _counter++;

    if (_counter % 50 == 0) {

        Board.Trace(Board.Format("counter:%d, EEPROM.isReady:%b", _counter, EEPROM.isReady()));
    }

    if (Serial.available()) {

        while (Serial.available()) {

            boolean executed = false;
            String s         = Serial.readStringUntil('\n');

            if (s == "resetCounter") {

                EEPROM.writeInt(eeprom_counter_addr, 0);
                _counter = 0;
                executed = true;
            }
            else if (s == "incCounter") {

                EEPROM.writeInt(eeprom_counter_addr, EEPROM.readInt(eeprom_counter_addr)+1);
                executed = true;
            }
            else if (s == "getCounter") {
                
                int v = EEPROM.readInt(eeprom_counter_addr);
                Board.Trace(Board.Format("[eeprom_counter:%d]", v));
                delay(10);
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
