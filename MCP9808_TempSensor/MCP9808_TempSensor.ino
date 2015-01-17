/**************************************************************************

This is a demo for the Adafruit MCP9808 breakout
http://www.adafruit.com/products/1782

*************************************************************************/

#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include "fArduino.h"

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
TimeOut _timeOut(1000L * 60 * 10);

#define ON_BOARD_LED 13

Led _onBoardLed(ON_BOARD_LED);

void AcquireData() {

    float c = tempsensor.readTempC();
    float f = c * 9.0 / 5.0 + 32;
    Board.Trace(StringFormat.Format("Celsius:%f, Fahrenheit:%f", c, f));
}

void setup() {

    Board.Delay(1500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("MCP9808 demo");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(500);

    // Make sure the sensor is found, you can also pass in a different i2c
    // address with tempsensor.begin(0x19) for example
    if (!tempsensor.begin()) {
        Board.Trace("[ERROR]Couldn't find MCP9808!");
        while (1);
    }

    Board.Trace(_timeOut.ToString());

    AcquireData();
}


void loop() {

    _onBoardLed.Blink();

    if (_timeOut.IsTimeOut()) {
        AcquireData();
    }
}