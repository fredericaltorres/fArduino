/*
    Controlling the tempetature sensor DS18B20 with the Arduino
    http://www.hobbytronics.co.uk/ds18b20-arduino
    http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

    Ref http://arduino.cc/en/Reference/HomePage
*/

#include "OneWire.h"
#include "fArduino.h"
#include "DS18B20TemperatureSensor.h"

#define ONE_WIRE_BUS 3

TimeOut                  _oneSecondTimeOut(1000);
TemperatureManager       _tempManager;
OneWire                  _oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices  (not just Maxim/Dallas temperature ICs)
DS18B20TemperatureSensor _DS18B20(&_oneWire);

void setup() {

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Tempetature Sensor DS18B20");
    //Board.ClearKeyboard();
    //Board.TraceFormat("Tempetature Sensor DS18B20 - Sensor ID:%d", _DS18B20.GetSensorId());
    Board.Trace("Ready...");
}

void loop() {

    if (_oneSecondTimeOut.IsTimeOut()) {

        Serial.println("Getting it");
        double celsius = _DS18B20.GetTemperature();
        //double fahrenheit = _tempManager.CelsiusToFahrenheit(celsius);
        //_tempManager.Add(celsius);
        Serial.println(celsius);
        //Board.Trace(Board.Format("[%s] %fC - %fF", Board.GetTime(), celsius, fahrenheit));
    }
}

