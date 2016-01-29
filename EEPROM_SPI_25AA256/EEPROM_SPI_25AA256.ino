/*
    Some code to test the SPI EEPROM 25AA256.
    So I can port the code to Nusbio/FT231X and FT232H

    http://ww1.microchip.com/downloads/en/DeviceDoc/21822G.pdf

    SPI ARDUINO 

    13-CLOCK
    12-MISO
    11-MOSI
    10-SELECT

    CS     [] [] VCC
   MISO/SO [] [] HOLD (Set HIGH while CLOCK is low)
   WP(HIGH)[] [] SCK
   GND     [] [] MOSI

   First test report reading the 32Kb in 215ms which mean ~ 152Kb/s at 10 Mhz.
*/

#include <SPI.h>
#include "25AA256.h"
#include <fArduino.h>

#define SS_PIN 10

#define EEPROM_25AA256_MAX_SPEED (10 * 1000 * 1000) // 10000000/8/1024/1024 ~=> 1.2 Mb/s

SPISettings spiSettings(EEPROM_25AA256_MAX_SPEED, MSBFIRST, SPI_MODE0);

EEPROM_25AA256 eeprom(32*1024, SS_PIN, &spiSettings);

const char EepromInitializationMessage[]        PROGMEM = { "Initializing EEPROM maxBlock:%d, maxBytes:%ui for testing" };
const char EepromVerification23kFastMessage[]   PROGMEM = { "Verify 32k fast" };
const char EepromInitializedInTimeMessage[]     PROGMEM = { "EEPROM Initialized in %l" };
const char EepromErrorInByteVerificationError[] PROGMEM = { "ERROR Page:%d, b[%d] = %d, expected:%d" }; // Index, value, expected
const char EepromErrorInByteVerificationOk[]    PROGMEM = { "OK--- Page:%d, b[%d] = %d, expected:%d" }; // Index, value, expected
const char EepromReadBufferFailed[]             PROGMEM = { "ReadBuffer() failed addr : %d" };
const char EepromWriteBufferFailed[]            PROGMEM = { "WriteBuffer() failed r:%d, block:%d" };
const char PageWrittenInfoMessage[]             PROGMEM = { "Page written r:%d, block:%d" };
const char EepromVerification23kSlowMessage[]   PROGMEM = { "Verify 32k 1 byte at the time" };
const char AppTitle[]                           PROGMEM = { "MadeInTheUSB - GDevice - EEPROM 24LC256 Testing" };
const char ProcessedInMessage[]                 PROGMEM = { "Processed in %l" };
const char PageXMessage[]                       PROGMEM = { "Page %d" };

byte refbuf   [EEPROM_25AA256_PAGE_SIZE]; // Init a 64 byte block
byte refbuf129[EEPROM_25AA256_PAGE_SIZE]; // Init a 64 byte block
byte refbuf255[EEPROM_25AA256_PAGE_SIZE]; // Init a 64 byte block

#define REF_VALUE_2 (128+1) // 10000001
#define REF_VALUE_3 (170)   // 10101010

void InitializeReferenceBufferWithRefValue2() {

    for (int i = 0; i < EEPROM_25AA256_PAGE_SIZE; i++) {
        refbuf129[i] = REF_VALUE_2;
    }
}

void InitializeReferenceBufferWithRefValue3() {

    for (int i = 0; i < EEPROM_25AA256_PAGE_SIZE; i++) {
        refbuf129[i] = REF_VALUE_3;
    }
}

void InitializeReferenceBuffer() {

    for (int i = 0; i < EEPROM_25AA256_PAGE_SIZE; i++) {
        refbuf[i] = i;
    }
    InitializeReferenceBufferWithRefValue2();
}

void WriteEEPROM() {

    InitializeReferenceBuffer();

    Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(EepromInitializationMessage), eeprom.MaxPage, eeprom.SizeInKb), true);

    unsigned long t = millis();
    bool r = false;

    for (int p = 0; p < eeprom.MaxPage; p++) { // Write the all 32k for the eeprom

        // eeprom.WriteBuffer() support the 30 byte Wire.h limitation by making 2 call to write the 64 bytes  :(
        // WriteBufferOneByteAtTheTime Write64ByteBuffer
        if (p == 2) {
            r = eeprom.Write64ByteBuffer(p * EEPROM_25AA256_PAGE_SIZE, EEPROM_25AA256_PAGE_SIZE, refbuf129);
        }
        else if (p == 3) {
            InitializeReferenceBufferWithRefValue3();
            r = eeprom.Write64ByteBuffer(p * EEPROM_25AA256_PAGE_SIZE, EEPROM_25AA256_PAGE_SIZE, refbuf129);
        }
        else {
            r = eeprom.Write64ByteBuffer(p * EEPROM_25AA256_PAGE_SIZE, EEPROM_25AA256_PAGE_SIZE, refbuf);
        }

        if (!r)
            Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(EepromWriteBufferFailed), r, p), true);

        if ((p % 10 == 0) || (p < 5))
            Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(PageWrittenInfoMessage), r, p), true);
    }
    t = millis() - t;
    Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(EepromInitializedInTimeMessage), t), true);
}

void ReadEEPROM() {

    InitializeReferenceBuffer();

    byte buf2[EEPROM_25AA256_PAGE_SIZE]; // Init a 64 byte block

    if (eeprom.SizeInKb < 0)
        Board.SendWindowsConsoleCommand("SOMETHING WRONG", true);

    Board.SendWindowsConsoleCommand(StringFormat.PM(EepromVerification23kFastMessage), true);
        
    unsigned long t = millis();

    for (int p = 0; p < eeprom.MaxPage; p++) { // Write the all 32k for the eeprom

        if (p % 256 == 0) 
            Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(PageXMessage), p), true);

        unsigned int ad = p * EEPROM_25AA256_PAGE_SIZE;
        // Read64ByteBufferOneAtTheTime Read64ByteBuffer
        bool r = eeprom.Read64ByteBuffer(ad, EEPROM_25AA256_PAGE_SIZE, buf2);
        if (r) {
            int errorCount = 0;
            for (int i = 0; i < EEPROM_25AA256_PAGE_SIZE; i++) {

                byte b = buf2[i];
                int expected = i;
                if (p == 2)
                    expected = REF_VALUE_2;
                if (p == 3)
                    expected = REF_VALUE_3;

                if (b != expected) {
                    errorCount++;
                    Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(EepromErrorInByteVerificationError), p, (ad + i), b, expected), true);
                }
                else {
                    if (p < 5){
                        //Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(EepromErrorInByteVerificationOk), p, (ad + i), b, expected), true);
                    }
                }
            }
        }
        else {
            Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(EepromReadBufferFailed), ad), true);
        }
    }
    t = millis() - t;
    Board.SendWindowsConsoleCommand(StringFormat.Format(StringFormat.PM(ProcessedInMessage), t), true);
}


void setup(void)
{
    // start serial port
    Board.Delay(2000);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("25AA256 EEPROM Testing");

    InitializeReferenceBuffer();
    
    Board.SendWindowsConsoleCommand(StringFormat.Format("maxPage:%d, SizeInKb:%ui", eeprom.MaxPage, eeprom.SizeInKb));

    //WriteEEPROM();
    ReadEEPROM();

    //Board.Trace("Write byte 0 and 1");
    //spiRam.write_byte(0, 1);
    //spiRam.write_byte(1, 2);
    //spiRam.write_byte(2, 3);
    //spiRam.write_byte(3, 4);

    /*Board.Trace("Readind byte 0 and 1");
    int b0 = (int)eeprom.read_byte(0);
    int b1 = (int)eeprom.read_byte(1);
    int b2 = (int)eeprom.read_byte(2);
    int b3 = (int)eeprom.read_byte(3);
    Board.Trace(StringFormat.Format("b0:%d, b1:%d, b2:%d, b3:%d", b0, b1, b2, b3));*/

}

void loop() {

}