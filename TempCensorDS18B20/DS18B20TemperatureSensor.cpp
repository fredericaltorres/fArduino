// 
// 
// 

#include "DS18B20TemperatureSensor.h"

DS18B20TemperatureSensor::DS18B20TemperatureSensor(OneWire * oneWire) {

    this->_oneWire = oneWire;
    this->_sensorId = 0;
}
DS18B20TemperatureSensor::~DS18B20TemperatureSensor(){

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
    return this->_sensorId;
}

double DS18B20TemperatureSensor::GetTemperature() {
    byte i;
    byte present = 0;
    byte data[12];
    byte addr[8];
    //find a device
    if (!this->_oneWire->search(addr)) {
        this->_oneWire->reset_search();
        return -32768;
    }
    if (OneWire::crc8(addr, 7) != addr[7]) {
        return -32768;
    }
    if (addr[0] != DS18S20_ID && addr[0] != DS18B20_ID) {
        return -32768;
    }
    this->_oneWire->reset();
    this->_oneWire->select(addr);
    
    this->_oneWire->write(0x44, 1); // Start conversion
    delay(850); // Wait some time...
    present = this->_oneWire->reset();
    this->_oneWire->select(addr);
    this->_oneWire->write(0xBE); // Issue Read scratchpad command
    for (i = 0; i < 9; i++) { // Receive 9 bytes
        data[i] = this->_oneWire->read();
    }
    // Calculate temperature value
    double temp = ((data[1] << 8) + data[0])*0.0625;
    return true;
}