/**************************************************************************

This is a demo for the Adafruit MCP9808 breakout
http://www.adafruit.com/products/1782

*************************************************************************/

#include "TwiMap.h"
#include "I2cMaster.h"
#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include "fArduino.h"

// Arduino and Trinket Pro: I2C SCL (Clock) A5, I2C SDA (Data) A4
//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

TimeOut _timeOut(1000L * 3);

#define ON_BOARD_LED 13

Led _onBoardLed(ON_BOARD_LED);

void AcquireData() {

  //  float c = tempsensor.readTempC();
    //float f = c * 9.0 / 5.0 + 32;
    //Board.Trace(StringFormat.Format("Celsius:%f, Fahrenheit:%f", c, f));
}

#define SDA_PIN 7
#define SCL_PIN 6

SoftI2cMaster rtc(SDA_PIN, SCL_PIN);

int8_t readDS1307(uint8_t address, uint8_t *buf, uint8_t count) {

    // issue a start condition, send device address and write direction bit
    if (!rtc.start(MCP9808_I2CADDR_DEFAULT | I2C_WRITE)) return -1;

    // send the DS1307 address
    if (!rtc.write(address)) return -2;

    // issue a repeated start condition, send device address and read direction bit
    if (!rtc.restart(MCP9808_I2CADDR_DEFAULT | I2C_READ))return -3;

    // read data from the DS1307
    for (uint8_t i = 0; i < count; i++) {

        // send Ack until last byte then send Ack
        buf[i] = rtc.read(i == (count - 1));
    }

    // issue a stop condition
    rtc.stop();
    return true;
}

uint8_t buffer[11];

void setup() {

    Board.Delay(1500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("MCP9808 demo");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(500);

    Board.Trace("Looking for MCP9808 ...");

    buffer[0] = 123;
    buffer[1] = 124;

    int sda = digitalRead(SDA_PIN);
    int scl = digitalRead(SCL_PIN);

    Board.Trace(StringFormat.Format("sda %d scl %d", sda, scl));
    
    int r = readDS1307(MCP9808_REG_MANUF_ID, buffer, 2);

    Board.Trace(StringFormat.Format("r:%d", r));
    Board.Trace(StringFormat.Format("val:%d, val2:%d", buffer[0], buffer[1]));

    // http://todbot.com/blog/2010/09/25/softi2cmaster-add-i2c-to-any-arduino-pins/comment-page-2/

    //// Make sure the sensor is found, you can also pass in a different i2c
    //// address with tempsensor.begin(0x19) for example
    //if (tempsensor.begin()) {
    //    Board.Trace("MCP9808 found");
    //}
    //else{
    //    Board.Trace("[ERROR]Couldn't find MCP9808!");
    //    while (1);
    //}

    Board.Trace(_timeOut.ToString());

    AcquireData();
}

void loop() {

    _onBoardLed.Blink();
    Board.Trace("Ok");

    if (_timeOut.IsTimeOut()) {
        AcquireData();
    }
    Board.Delay(1000);
}