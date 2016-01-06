/*
MCP4131 example

Example to test MCP4131 from sparkfun: http://www.sparkfun.com/products/10613

Circuit:
* MCP4131 attached to pins 10, 11, 12, 13
* SDO is connected to a 4.7K resitor before it connect to the shared SDI/SDO Pin
* Analog inputs attached to pins A0 through A5 (optional)

Example Created by Dennis Liang on 11/20/2011
Orginal MCP4161 implementation from https://github.com/declanshanaghy/ArduinoLibraries/tree/master/MCP4161

// https://github.com/LinkedMink/MCP41XX-42XX-for-Arduino

*/

#include <SPI.h>
#include <MCP4131.h>
#include "fArduino.h"

//setup an intance of MCP4131
MCP4131 MCP4131(10); // with a CS pin of 10
int incomingByte = 0;

long previousMillis = 0;        // will store last time LED was updated

int tapValue = 1;        // will store last time LED was updated


void setup(void)
{
    // start serial port
    Board.Delay(500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("MCP4131 Digital Potentiometer demo");
    Board.SetPinMode(10, OUTPUT);


    MCP4131.setTap(MCP4131_MIN); //Sets the pot to 0.
    //MCP4131.setTap(MCP4131_MAX); //Sets the pot to MAX.
    if (!MCP4131.initTCON())  //init the pot, connect wiper0, and turn ON pot
    {
        Serial.println("Init Error!");
    }
}

/*

in [XX] Arduino pins and GND and POWER to Arduibo GND and POWER.

CS[10]              VDD(POWER)
SCK[13]             P0B(POT GND)
SDI/SDO[11]         P0W(POT OUTPUT)
VSS(GND)            P0A(POT POWER)


On an Arduino
    Clock: 13
    MISO: 12
    MOSI: 11
    SS: 10

*/

#define POT_RESISTANCE 10000
#define POT_STEP 128

void loop(void)
{
    delay(333);

    double resistance = POT_RESISTANCE - (POT_RESISTANCE / POT_STEP * tapValue);
    double voltage    = 5;
    double amp        = voltage * 1000 / resistance;
    double power      = voltage * amp;

    Board.Trace(StringFormat.Format("Digital pot value:%d, Res:%f Ohm, Volt:%f, Amp:%f, Pwr:%f", tapValue, resistance, voltage, amp, power));

    if (MCP4131.setTap(tapValue)) {
        Board.Trace("Ok");
        delay(100);
    }
    else
        Board.Trace("setTap Error!");

    tapValue++;
    if (tapValue >= 128)
        tapValue = 0;

    /*if(MCP4131.readTap()) {
        Board.Trace(StringFormat.Format("Read Value:%d", MCP4131.Wiper_Reg));
    }*/
    delay(100);

    return;
    
    if (MCP4131.readTCON() == true)
    {
        Serial.print("TCON:");
        Serial.println(MCP4131.Tcon_Reg, BIN); ///wipper and shutdown control bits //should be all one
    }

    if (MCP4131.readStatus() == true)
    {
        Serial.print("STATUS:");
        Serial.println(MCP4131.Status_Reg, BIN); ///wipper and shutdown control bits //should be all one
    }

    if (MCP4131.readTap() == true)
    {
        Serial.print("WIPER:");
        Serial.println(MCP4131.Wiper_Reg, DEC); //Where the wiper position
    }

    if (!MCP4131.setTap(tapValue))
    {
        Serial.println("setTap Error!");
    }
    else
    {
        tapValue++;
        if (tapValue > 128)
        {
            tapValue = 0;
        }
        Serial.print("WIPER AFTER SET:");
        Serial.println(MCP4131.Wiper_Reg, DEC); //Wiper register is updated
    }

    if (!MCP4131.increment())
    {
        Serial.println("increment Error!"); //Try to Increment
    }

    if (MCP4131.readTap() == true)
    {
        Serial.print("WIPER AFTER INCREMENT:");
        Serial.println(MCP4131.Wiper_Reg, DEC);
    }

    if (!MCP4131.decrement())
    {
        Serial.println("decrement Error!"); //Try to decrement
    }

    if (MCP4131.readTap() == true)
    {
        Serial.print("WIPER AFTER DECREMENT:");
        Serial.println(MCP4131.Wiper_Reg, DEC);
    }



}
