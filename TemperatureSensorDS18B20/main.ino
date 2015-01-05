/***********************************************************************

Acquiring and storing temperature with Arduino and a DS18B20 sensor

- Acquiring temperature data every 6 minutes. 
- Store the data into an EPROM Array. Sore 3 days of data on 512 bytes of EPROM.
- Api to communicate with a Windows Console to
    - resetData
    - getData: Send acquired data as CSV to the WindowsConsole (Serial port)
    - acquireData
- Use fArduino library to write clean and readable code

- User interface on the arduino:
    Use on board led, to express that the application state:
    1) if blinking on/off every 1/2 second, the application is waiting, normal state
    2) if blinking on/off for 1.6 second quickly, the application just acquire a new temperature
    3) if blinking on/off for 4 seconds semi-quickly repeatedly, There is an issue with the sensor

***********************************************************************/

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

// Use on board led, to express that the application state:
//  1) if blinking on/off every 1/2 second, the application is waiting, normal state
//  2) if blinking on/off for 1.6 second quickly, the application just acquire a new temperature
//  3) if blinking on/off for 4 seconds semi-quickly repeatedly, There is an issue with the sensor
Led _onBoardLed(ON_BOARD_LED);
boolean _ledState = false;
#define ON_BOARD_LED_NORMAL_BLINKING_RATE 500 // 500 milli-seconds

// Data Management
// Trigger every 6 minutes ==- 3days * 24hours * 6minutes ==- 432 byte
// From the moment we started the app
#define MAX_TEMPERATURE_SAMPLES 3 * 24 * 6          // 3days * 24hours * 6minutes ==- 432 byte
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
    int lastTemp      = _temperatureDB.AddByteArray((byte)Board.RoundDouble(celsius));
    Board.Trace(StringFormat.Format("celsius:%f, fahrenheit:%f, celsius(byte):%d", celsius, fahrenheit, lastTemp));
    _onBoardLed.Blink(10, 40);   // Blink led for 1.6 second quickly to signal we just acquire a new value
    _acquisitionTimeOut.Reset(); // Reset time out in case the acquisition was manually requested
}

void CheckForIssueWithSensor() {

    double celsius = _DS18B20.GetTemperature();
    if (abs(celsius) > ABNORMAL_TEMPERATURE) {

        Board.Trace(StringFormat.Format("Temperature sensor issue celsius:%f", celsius));
        _onBoardLed.Blink(20, 100); // Blink led for 4 seconds, semi-quickly
        _monitorTimeOut.Reset();    // Restart counting from now, after we blinked the led
    }
}

void setup() {

    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Temperature Logger - Sensor:DS18B20");

    Board.SetPinMode(ON_BOARD_LED, OUTPUT);

    MemDB::InitEEPROM(Board.GetEEPROMSize(), MAX_TEMPERATURE_SAMPLES * 3);
    _temperatureDB.CreateByteArray(MAX_TEMPERATURE_SAMPLES, false);
    Board.Trace(StringFormat.Format("Temperature Count:%d", _temperatureDB.GetLength()));
    Board.Trace(StringFormat.Format("Acquire data every %ul second(s)", SAMPLING_TIME));

    Board.Trace(StringFormat.Format("Sensor ID:%d, Name:%s",_DS18B20.GetSensorId(), _DS18B20.GetSensorName()));

    // The onboard led will blink on/off every 1/2 seconds to signal app is running
    _onBoardLed.SetBlinkMode(ON_BOARD_LED_NORMAL_BLINKING_RATE);

    AcquireData();
}

void loop() {

    _onBoardLed.Blink(); // Blink led every 1/2 second

    if (_monitorTimeOut.IsTimeOut()) {

        CheckForIssueWithSensor();
    }
    if (_acquisitionTimeOut.IsTimeOut()) {

        AcquireData();
    }

    // Process commands coming from the WindowsConsole
    WindowsCommand winCommand = Board.GetWindowsConsoleCommand(); // The WindowsConsole method use the Serial port communication

    if (winCommand.Command == "resetData") {

        _temperatureDB.ClearByteArray();
        Board.SendWindowsConsoleCommand("No temperatures stored");
    }
    else if (winCommand.Command == "acquireData") {

        AcquireData();
    }
    else if (winCommand.Command == "getData") {

        if (_temperatureDB.GetLength() == 0) {

            Board.SendWindowsConsoleCommand("No temperatures stored");
        }
        else {
            Board.SendWindowsConsoleCommand("<data>");
            _temperatureDB.ToSerial();
            Board.Delay(200);
            Board.SendWindowsConsoleCommand("<data>");
        }
    }
    else {
        if (winCommand.Command != "") {
            Board.SendWindowsConsoleCommand(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
        }
    }
}
