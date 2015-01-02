/************************************

    http://arduino.cc/en/Reference/HomePage

    http://playground.arduino.cc/Interfacing/Csharp
    http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging

    TV for $1 - https://www.youtube.com/watch?v=WlBXiZpuncg

*/

#include "fArduino.h"

#define ON_BOARD_LED 13
boolean _ledState = false;

// Trigger every 6 minutes - 6 time per hour => 144 value per day 
// 432 bytes represent 3 days of data, starting from 
//    - the moment we started the Arduino
//    - One mesure every 6 minutes
#define MAX_TEMPERATURE_SAMPLES 3 * 24 * 6 // 3d * 24h * 6m ==> 432
TimeOut _timeOut(1000 * 60 * 6); 
MemDB _temperatureDB; // Trinket has only 512 byte of EPROM

void setup() {

    Board.Delay(1000); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Serial Communicator With EEPROM");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    
    MemDB::InitEEPROM(512, MAX_TEMPERATURE_SAMPLES * 3);
    int temperatureDBAddr = _temperatureDB.CreateByteArray(MAX_TEMPERATURE_SAMPLES, false);
    
    Board.TraceFormat("temperatureDBAddr:%d", temperatureDBAddr);
    Board.TraceFormat("temperature Length:%d", _temperatureDB.GetLength());

    Board.Trace(_timeOut.ToString());
}

void PowerLed(boolean state) {

    Board.LedOn(ON_BOARD_LED, state);
}

void loop() {

    if (_timeOut.IsTimeOut()) {

        int lastTemp = _temperatureDB.AddByteArray((byte)millis());
        Board.TraceFormat("LastTemperature:%d", lastTemp);
    }

    if (Serial.available()) {

        while (Serial.available()) {

            boolean executed = false;
            String s         = Serial.readStringUntil('\n');

            if (s == "resetCounter") {

                _temperatureDB.Clear();
                Board.Trace("No temperatures stored");
                executed = true;
            }
            else if (s == "incCounter") {

                _temperatureDB.AddByteArray((byte)millis());
                executed = true;
            }
            else if (s == "getCounter") {
                
                if (_temperatureDB.GetLength() == 0) {
                    Board.Trace("No temperatures stored");
                }
                else {
                    Board.Trace(_temperatureDB.ToString());
                }
                Board.Trace(_timeOut.ToString());
                executed = true;
            }
            else if (s == "led") {

                _ledState = !_ledState;
                Board.LedOn(ON_BOARD_LED, _ledState);
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
