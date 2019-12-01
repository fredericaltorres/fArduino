// DS18B20TemperatureSensor.h

#ifndef _DS18B20TEMPERATURESENSOR_h
#define _DS18B20TEMPERATURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "OneWire.h"

#define DS18B20TemperatureSensor_SearchFailed        -1
#define DS18B20TemperatureSensor_CrcFailed           -2
#define DS18B20TemperatureSensor_UnknownSensor       -3
#define DS18B20TemperatureSensor_GetTemperatureError -32768

#define DS18X20_UNKNOWN_ID 0x00
#define DS18S20_ID         0x10
#define DS18B20_ID         0x28

#define DS18X20_WAIT_TIME_FOR_GET_TEMPERATURE 800

/******************************************************************************************
DS18B20TemperatureSensor

    DataSheet: http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
    Comparing the DS18S20 and the DS18B20: http://www.maximintegrated.com/en/app-notes/index.mvp/id/4377
*/
class DS18B20TemperatureSensor {
    private:
        OneWire * _oneWire;
        byte _addr[8];
        byte _sensorId;
    public:
        DS18B20TemperatureSensor(OneWire * oneWire);
        ~DS18B20TemperatureSensor();
        int GetSensorId();
        char * GetSensorName();
        double GetTemperature();
        double CelsiusToFahrenheit(double celsius);
        String GetSensorUniqueIdsOn1Wire();
};
#endif

