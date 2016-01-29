// 
// 
// 

#include <SPI.h>
#include "25AA256.h"

EEPROM_25AA256::EEPROM_25AA256(byte clockDiv, byte ssPin, SPISettings * spiSettings)
{
    this->_spiSettings = spiSettings;
    SPI.begin();
    unselect(false);
    _ssPin = ssPin;    
}


// select and unselect helper functions

void EEPROM_25AA256::select(bool transaction)
{
    if (transaction)
        SPI.beginTransaction(*this->_spiSettings);  // gain control of SPI bus
    digitalWrite(_ssPin, LOW);
}

void EEPROM_25AA256::unselect(bool transaction)
{
    if (transaction)
        SPI.endTransaction();
    digitalWrite(_ssPin, HIGH);
}

char EEPROM_25AA256::read_byte(int address)
{
    char read_byte;

    this->select(true);

    SPI.transfer(READ);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    read_byte = SPI.transfer(0xFF);

    this->unselect(true);
    
    return read_byte;
}

char EEPROM_25AA256::write_byte(int address, char data_byte)
{
    this->Wren();
    
    this->select(true);

    SPI.transfer(WRITE);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    SPI.transfer(data_byte);

    this->unselect(true);

    SPI.endTransaction();
    delay(5);
    
    return data_byte;
}

void EEPROM_25AA256::Wren()
{
    this->select(true);
    SPI.transfer(WREN);
    this->unselect(true);
}

bool EEPROM_25AA256::Read64ByteBuffer(int address, int size, byte *buffer)
{
    this->select(true);

    SPI.transfer(READ);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    for (int i = 0; i < size; i++) {
        buffer[i] = SPI.transfer(0xFF);
    }

    this->unselect(true);
    return true;
}

bool EEPROM_25AA256::Write64ByteBuffer(int address, int size, byte *buffer)
{
    int i;
    this->Wren(); // activate write enable mode
    this->select(true);
    SPI.transfer(WRITE);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    for (i = 0; i < size; i++) {
        SPI.transfer(buffer[i]);
    }
    this->unselect(true);
    delay(5);
    return true;
}
