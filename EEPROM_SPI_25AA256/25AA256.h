// 25AA256.h

#ifndef _25AA256_h
#define _25AA256_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SPI.h>


// SRAM opcodes
#define WREN  6 // Write Enable
#define WRDI  4 // Write Disable
#define RDSR  5 // Read Status Register Instruction 
#define WRSR  1 // Write Status Register Instruction 
#define READ  3
#define WRITE 2

// SRAM Hold line override
#define HOLD 1

// SRAM modes
#define BYTE_MODE (0x00 | HOLD)
#define PAGE_MODE (0x80 | HOLD)
#define STREAM_MODE (0x40 | HOLD)

// Clock speeds
#define RAMCLK4M   0
#define RAMCLK1M   1
#define RAMCLK250K 2
#define RAMCLK125K 3

class EEPROM_25AA256
{
public:
    EEPROM_25AA256(byte clock, byte ssPin, SPISettings * spiSettings);
    void select(bool transaction);
    void unselect(bool transaction);
    char read_byte(int address);
    char write_byte(int address, char data_byte);    
    bool Read64ByteBuffer(int address, int size, byte *buffer);
    bool Write64ByteBuffer(int address, int size, byte *buffer);
private:
    byte _ssPin;
    SPISettings * _spiSettings;
    void Wren();
};


#endif

