// 
// 
// 

#include "DS18B20TemperatureSensor.h"

char * __DS18X20_TEMP_SENSORS[] = { "UNKNOWN", "DS18S20", "DS18B20" };

DS18B20TemperatureSensor::DS18B20TemperatureSensor(OneWire * oneWire) {

    this->_oneWire = oneWire;
    this->_sensorId = 0;
}
DS18B20TemperatureSensor::~DS18B20TemperatureSensor(){

}
char * DS18B20TemperatureSensor::GetSensorName(){

    int index = DS18X20_UNKNOWN_ID;
    int id    = this->GetSensorId();

    switch (id) {

        case DS18S20_ID: index = 1; break;
        case DS18B20_ID: index = 2; break;
    }
    return __DS18X20_TEMP_SENSORS[index];
}
double DS18B20TemperatureSensor::CelsiusToFahrenheit(double celsius) {

    return (9.0 / 5.0 * celsius) + 32.0;
}
int DS18B20TemperatureSensor::GetSensorId(){

    byte i;
    byte present = 0;
    byte data[12];

    if (!this->_oneWire->search(this->_addr)) {

        this->_oneWire->reset_search();
        return DS18B20TemperatureSensor_SearchFailed;
    }
    if (OneWire::crc8(this->_addr, 7) != this->_addr[7]) {

        return DS18B20TemperatureSensor_CrcFailed;
    }
    if (this->_addr[0] != DS18S20_ID && this->_addr[0] != DS18B20_ID) {

        return DS18B20TemperatureSensor_UnknownSensor;
    }
    this->_sensorId = this->_addr[0];

    this->_oneWire->reset_search(); // Always reset the search

    return this->_sensorId;
}
// http://forum.arduino.cc/index.php?topic=40211.0
double DS18B20TemperatureSensor::GetTemperature() {
    byte i;
    byte data[12];
    byte addr[8];
    
    if (!this->_oneWire->search(addr)) { // Find the sensor
        this->_oneWire->reset_search();
        return DS18B20TemperatureSensor_GetTemperatureError;
    }
    if (OneWire::crc8(addr, 7) != addr[7]) {
        return DS18B20TemperatureSensor_GetTemperatureError;
    }
    if (addr[0] != DS18S20_ID && addr[0] != DS18B20_ID) {
        return DS18B20TemperatureSensor_GetTemperatureError;
    }
    this->_oneWire->reset();
    this->_oneWire->select(addr);
    this->_oneWire->write(0x44, 1);

    delay(DS18X20_WAIT_TIME_FOR_GET_TEMPERATURE);

    byte available = this->_oneWire->reset();
    this->_oneWire->select(addr);
    this->_oneWire->write(0xBE); // Send read scratchpad command
    for (i = 0; i < 9; i++) {
        data[i] = this->_oneWire->read();
    }
    double temp = ((data[1] << 8) + data[0])*0.0625;
    this->_oneWire->reset_search(); // Always reset the search
    return temp;
}

String DS18B20TemperatureSensor::GetSensorUniqueIdsOn1Wire() {

    byte i;
    byte present = 0;
    byte data[12];
    byte addr[8];
    String sensorUniqueId("");

    this->_oneWire->reset_search();

    while(this->_oneWire->search(addr)) {
                
        sensorUniqueId += "{ ";

        for(i = 0; i < 8; i++) {

            if(addr[i] < 16) {
                sensorUniqueId += "0";
            }
            sensorUniqueId += addr[i];
            if(i < 7) {
                sensorUniqueId += ", ";
            }
        }
        if(OneWire::crc8(addr, 7) != addr[7]) {
            return "CRC is not valid!";
        }
        sensorUniqueId += " }";
    }
    //Serial.println(sensorUniqueId);
    this->_oneWire->reset_search();
    return sensorUniqueId;
}