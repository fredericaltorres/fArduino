/*

SPI EEPROM 25AA256

Copyright (C) 2016 MadeInTheUSB LLC
Written by FT

http://www.MadeInTheUSB.net

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <SPI.h>
#include "25AA256.h"

EEPROM_25AA256::EEPROM_25AA256(unsigned int sizeInKb, byte ssPin, SPISettings *spiSettings)
{
    this->SizeInKb     = sizeInKb;
    this->MaxPage      = this->SizeInKb / EEPROM_25AA256_PAGE_SIZE;
    this->_spiSettings = spiSettings;
    SPI.begin();
    this->Unselect(false);
    this->_ssPin = ssPin;
}

void EEPROM_25AA256::Select(bool transaction)
{
    if (transaction)
        SPI.beginTransaction(*this->_spiSettings);  // gain control of SPI bus
    digitalWrite(_ssPin, LOW);
}

void EEPROM_25AA256::Unselect(bool transaction)
{
    if (transaction)
        SPI.endTransaction();
    digitalWrite(_ssPin, HIGH);
}

char EEPROM_25AA256::ReadByte(int address)
{
    char read_byte;

    this->Select(true);

    SPI.transfer(READ);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    read_byte = SPI.transfer(0xFF);

    this->Unselect(true);
    
    return read_byte;
}

char EEPROM_25AA256::WriteByte(int address, char data_byte)
{
    this->Wren();
    
    this->Select(true);
    SPI.transfer(WRITE);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    SPI.transfer(data_byte);
    this->Unselect(true);
    delay(5);
    
    return data_byte;
}

void EEPROM_25AA256::Wren()
{
    this->Select(true);
    SPI.transfer(WREN);
    this->Unselect(true);
}

bool EEPROM_25AA256::Read64ByteBuffer(int address, int size, byte *buffer)
{
    this->Select(true);

    SPI.transfer(READ);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    for (int i = 0; i < size; i++) {
        buffer[i] = SPI.transfer(0xFF);
    }
    this->Unselect(true);
    return true;
}

bool EEPROM_25AA256::Write64ByteBuffer(int address, int size, byte *buffer)
{
    int i;

    this->Wren(); // activate write enable mode

    this->Select(true);

    SPI.transfer(WRITE);
    SPI.transfer((char)(address >> 8));
    SPI.transfer((char)address);
    for (i = 0; i < size; i++) {
        SPI.transfer(buffer[i]);
    }

    this->Unselect(true);
    delay(5);
    return true;
}
