/*
    Controlling the tempetature sensor DS18B20 with the Arduino
    http://www.hobbytronics.co.uk/ds18b20-arduino
    http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
    Ref http://arduino.cc/en/Reference/HomePage
*/

#include "OneWire.h"
#include "fArduino.h"
#include "DS18B20TemperatureSensor.h"

#define ONE_WIRE_BUS 2

TimeOut                  _oneSecondTimeOut(1000);
OneWire                  _oneWire(ONE_WIRE_BUS);
DS18B20TemperatureSensor _DS18B20(&_oneWire);

void setup() {

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Tempetature Sensor DS18B20");
    Board.Trace(Board.Format("Tempetature Sensor ID:%d, Name:%s", _DS18B20.GetSensorId(), _DS18B20.GetSensorName()));
    Board.Trace("Ready...");
}

void loop() {

    static double previousCelsius;

    if (_oneSecondTimeOut.IsTimeOut()) {

        double celsius = _DS18B20.GetTemperature();

        if (previousCelsius != celsius || _oneSecondTimeOut.EveryCalls(10)) {
            
            double fahrenheit = _DS18B20.CelsiusToFahrenheit(celsius);
            Board.Trace(Board.Format("[%s, mem:%d] %fC - %fF", Board.GetTime(), Board.GetFreeMemory(), celsius, fahrenheit));
            previousCelsius = celsius;
        }
    }
}
