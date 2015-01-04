/************************************

http://arduino.cc/en/Reference/HomePage

http://playground.arduino.cc/Interfacing/Csharp
http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging

TV for $1 - https://www.youtube.com/watch?v=WlBXiZpuncg

*/

#include "OneWire.h"
#include "fArduino.h"
#include "DS18B20TemperatureSensor.h"

// Pins usage
#if TRINKET
    #define ON_BOARD_LED 1
#else
    #define ON_BOARD_LED 13
#endif
#define ONE_WIRE_BUS 4

Led _onBoardLed(ON_BOARD_LED); // Use on board led, to express the application is or waiting or just acquire a temperature
boolean _ledState = false;

// Data Management
// Trigger every 6 minutes => 3days * 24hours * 6minutes ==> 432 byte
// From the moment we started the app
#define MAX_TEMPERATURE_SAMPLES 3 * 24 * 6          // 3days * 24hours * 6minutes ==> 432 byte
#define SAMPLING_TIME           1000UL * 60UL * 6UL // Every 6 minutes -- Must be unsigned long

TimeOut _acquisitionTimeOut(SAMPLING_TIME);
MemDB _temperatureDB;                               // Reminder:Trinket has only 512 bytes of EPROM

// Data Acquisition
OneWire                  _oneWire(ONE_WIRE_BUS);
DS18B20TemperatureSensor _DS18B20(&_oneWire);

// Timeout to make sure the sensor is working
TimeOut _monitorTimeOut(1000);
#define ABNORMAL_TEMPERATURE 100 // Celcius

double CelsiusToFahrenheit(double celsius) {

    return (9.0 / 5.0 * celsius) + 32.0;
}

void AcquireData() {

    double celsius    = _DS18B20.GetTemperature();
    double fahrenheit = CelsiusToFahrenheit(celsius);
    int lastTemp      = _temperatureDB.AddByteArray((byte)(int)celsius);
    Board.Trace(StringFormat.Format("celsius:%f, fahrenheit:%f, celsius(byte):%d", celsius, fahrenheit, lastTemp));
    _onBoardLed.Blink(10, 40); // Blink led 10 time quickly to signal we just acquire a new value    
}

void CheckForIssueWithSensor() {

    double celsius = _DS18B20.GetTemperature();
    if (abs(celsius) > ABNORMAL_TEMPERATURE) {

        Board.Trace(StringFormat.Format("Temperature sensor issue celsius:%f", celsius));
        _onBoardLed.Blink(20, 75); // Blink led for 2 seconds
        _monitorTimeOut.Reset();    // Restart countring from now, after we blinked the led
    }
}

void setup() {

    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Temperature Logger - Sensor:DS18B20");

    Board.SetPinMode(ON_BOARD_LED, OUTPUT);

    MemDB::InitEEPROM(Board.GetEEPROMSize(), MAX_TEMPERATURE_SAMPLES * 3);
    int temperatureDBAddr = _temperatureDB.CreateByteArray(MAX_TEMPERATURE_SAMPLES, false);
    Board.Trace(StringFormat.Format("Temperature Count:%d", _temperatureDB.GetLength()));
    Board.Trace(StringFormat.Format("Acquire data every %ul second(s)", SAMPLING_TIME));

    Board.Trace(_acquisitionTimeOut.ToString());

    Board.Trace(StringFormat.Format("Sensor ID:%d, Name:%s",_DS18B20.GetSensorId(), _DS18B20.GetSensorName()));
    //Board.Trace(StringFormat.Format("Sensor Unique ID:%s", _DS18B20.GetSensorUniqueIdsOn1Wire()));
    
    // The onboard led will blink on/off every 1/2 seconds to signal app is running
    _onBoardLed.SetBlinkMode(500);

    AcquireData();
}

void loop() {

    _onBoardLed.Blink(); // Blink led every second

    if (_monitorTimeOut.IsTimeOut()) {

        CheckForIssueWithSensor();
    }

    if (_acquisitionTimeOut.IsTimeOut()) {

        AcquireData();
    }

    if (Serial.available()) {

        while (Serial.available()) {

            boolean executed = false;
            String s = Serial.readStringUntil('\n');

            if (s == "resetData") {

                _temperatureDB.Clear();
                Board.Trace("No temperatures stored");
                executed = true;
            }
            if (s == "acquireData") {

                AcquireData();
                executed = true;
            }
            else if (s == "getData") {

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
