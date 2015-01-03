/************************************

http://arduino.cc/en/Reference/HomePage

http://playground.arduino.cc/Interfacing/Csharp
http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging

TV for $1 - https://www.youtube.com/watch?v=WlBXiZpuncg

*/

#include "OneWire.h"
#include "fArduino.h"
#include "DS18B20TemperatureSensor.h"

#if TRINKET
    #define ON_BOARD_LED 1
#else
    #define ON_BOARD_LED 13
#endif

#define ONE_WIRE_BUS 4

boolean _ledState = false;

// Trigger every 6 minutes - 6 time per hour => 144 value per day 
// 432 bytes represent 3 days of data, starting from 
//    - the moment we started the Arduino
//    - One mesure every 6 minutes
#define MAX_TEMPERATURE_SAMPLES 3 * 24 * 6 // 3d * 24h * 6m ==> 432
//#define SAMPLING_TIME           1000UL * 60UL * 1UL // Must be unsigned long
#define SAMPLING_TIME           1000UL * 10UL // Must be unsigned long
TimeOut _timeOut(SAMPLING_TIME);
MemDB _temperatureDB; // Trinket has only 512 byte of EPROM

OneWire                  _oneWire(ONE_WIRE_BUS);
DS18B20TemperatureSensor _DS18B20(&_oneWire);

Led _onBoardLed(ON_BOARD_LED);  // The led representing the User Interface

double CelsiusToFahrenheit(double celsius) {

    return (9.0 / 5.0 * celsius) + 32.0;
}

void setup() {

    Board.Delay(1500); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Temperature Logger - Sensor:DS18B20");

    Board.SetPinMode(ON_BOARD_LED, OUTPUT);

    MemDB::InitEEPROM(512, MAX_TEMPERATURE_SAMPLES * 3);
    int temperatureDBAddr = _temperatureDB.CreateByteArray(MAX_TEMPERATURE_SAMPLES, false);
    Board.Trace(StringFormat.Format("Temperature Count:%d", _temperatureDB.GetLength()));

    Board.Trace(_timeOut.ToString());

    Board.Trace(StringFormat.Format("Sensor ID:%d, Name:%s",_DS18B20.GetSensorId(), _DS18B20.GetSensorName()));

    // The onboard led will blink on/off every 1/2 seconds to signal app is running
    _onBoardLed.SetBlinkMode(500);
}

void loop() {

    _onBoardLed.Blink(); // Blink led every second

    if (_timeOut.IsTimeOut()) {

        double celsius    = _DS18B20.GetTemperature();
        double fahrenheit = CelsiusToFahrenheit(celsius);
        int lastTemp      = _temperatureDB.AddByteArray((byte)(int)celsius);
        Board.Trace(StringFormat.Format("celsius:%f, fahrenheit:%f, celsius(byte):%d", celsius, fahrenheit, lastTemp));
        _onBoardLed.Blink(10, 40); // Blink led 10 time quickly to signal we just acquire a new value
    }

    if (Serial.available()) {

        while (Serial.available()) {

            boolean executed = false;
            String s = Serial.readStringUntil('\n');

            if (s == "resetCounter") {

                _temperatureDB.Clear();
                Board.Trace("No temperatures stored");
                executed = true;
            }
            else if (s == "getCounter") {

                if (_temperatureDB.GetLength() == 0) {
                    Board.Trace("No temperatures stored");
                }
                else {
                    _temperatureDB.ToSerial();
                    Board.Trace("<data-dumped>", false);
                }
                executed = true;
            }
            if (!executed) {
                Board.Trace(StringFormat.Format("[Invalid command:%s]", s.c_str()));
            }
        }
    }
}
