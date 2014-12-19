// DS18B20TemperatureSensor.h

#ifndef _DS18B20TEMPERATURESENSOR_h
#define _DS18B20TEMPERATURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "OneWire.h"

#define DS18B20TemperatureSensor_SearchFailed   -1
#define DS18B20TemperatureSensor_CrcFailed      -2
#define DS18B20TemperatureSensor_UnknownSensor  -3
#define DS18S20_ID 0x10
#define DS18B20_ID 0x28

class DS18B20TemperatureSensor {
    private:
        OneWire * _oneWire;
        byte _addr[8];
        byte _sensorId;
    public:
        DS18B20TemperatureSensor(OneWire * oneWire);
        ~DS18B20TemperatureSensor();
        int GetSensorId();
        double GetTemperature();
};
#endif

