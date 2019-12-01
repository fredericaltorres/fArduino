/*
Controlling the tempetature sensor DS18B20 with the Arduino
http://www.hobbytronics.co.uk/ds18b20-arduino
http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

Ref http://arduino.cc/en/Reference/HomePage
*/
/*
#include "OneWire.h"
#include "DallasTemperature.h"
#include "fArduino.h"

struct tm * a;

#define ONE_WIRE_BUS 2

OneWire             _oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices  (not just Maxim/Dallas temperature ICs)
DallasTemperature   _tempDS18B20Sensor(&_oneWire); // Pass our oneWire reference to Dallas Temperature.
TimeOut             _oneSecondTimeOut(1000);
TemperatureManager  _tempManager;

void setup() {

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Tempetature Sensor DS18B20 ");
    //Board.ClearKeyboard();
    Board.Trace("Ready...");

    _tempDS18B20Sensor.begin();
}

void loop() {

    if (_oneSecondTimeOut.IsTimeOut()) {

        double celsius = _tempDS18B20Sensor.getTempCByIndex(0);
        double fahrenheit = _tempManager.CelsiusToFahrenheit(celsius);
        _tempManager.Add(celsius);

        Board.Trace(Board.Format("[%s] %fC - %fF", Board.GetTime(), celsius, fahrenheit));
    }
}

*/