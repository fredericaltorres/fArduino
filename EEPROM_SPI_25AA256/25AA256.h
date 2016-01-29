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

// 25AA256.h

#ifndef _25AA256_h
#define _25AA256_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SPI.h>

#define EEPROM_25AA256_PAGE_SIZE 64

#define WREN  6 // Write Enable
#define WRDI  4 // Write Disable
#define RDSR  5 // Read Status Register Instruction 
#define WRSR  1 // Write Status Register Instruction 
#define READ  3
#define WRITE 2

class EEPROM_25AA256
{
public:
    EEPROM_25AA256(unsigned int sizeInKb, byte ssPin, SPISettings * spiSettings);
    void Select(bool transaction);
    void Unselect(bool transaction);
    char ReadByte(int address);
    char WriteByte(int address, char data_byte);    
    bool Read64ByteBuffer(int address, int size, byte *buffer);
    bool Write64ByteBuffer(int address, int size, byte *buffer);
    unsigned int SizeInKb;
    int MaxPage;
private:
    byte _ssPin;
    SPISettings * _spiSettings;
    void Wren();
};


#endif

