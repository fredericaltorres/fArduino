///**************************************************************************
//
//http://www.learningaboutelectronics.com/Articles/MCP4131-digital-potentiometer-circuit.php
//
//Ohm's Law Calculator
//
//http://www.ohmslawcalculator.com/ohms-law-calculator
//
//Using a Digital Pot & IR Remote to Control Contrast of an LCD with an Arduino Uno
//http://bradsduino.blogspot.com/2013/01/using-digital-pot-ir-remote-to-control.html
//
//About SPI
//http://tronixstuff.com/2011/05/13/tutorial-arduino-and-the-spi-bus/
//
//Arduino Theremin
//http://blog.jacobean.net/?p=766
//-
//https://github.com/dreamcat4/Mcp4261/blob/master/Mcp4261.cpp
//https://github.com/jmalloc/arduino-mcp4xxx
//https://github.com/declanshanaghy/ArduinoLibraries/tree/master/MCP4161
//
//4131 for arduino
//http://www.learningaboutelectronics.com/Articles/MCP4131-digital-potentiometer-circuit.php
//
//*************************************************************************/
//
////#include "SoftI2CMaster.h"
//#include <SPI.h>
//#include <mcp4xxx.h>
//#include "fArduino.h"
//
//
//
//int CS = 10;
//
//
///*
//
//in [XX] Arduino pins and GND and POWER to Arduibo GND and POWER.
//
//CS[10]              VDD(POWER)
//SCK[13]             P0B(POT GND)
//SDI/SDO[11]         P0W(POT OUTPUT)
//VSS(GND)            P0A(POT POWER)
//
//*/
//
//TimeOut _timeOut(1000L * 3);
//
//MCP4XXX* pot;
//
//
//void setup() {
//
//    /*MCP4XXX::Pot p = MCP4XXX::Pot::pot_0;
//    MCP4XXX::Resolution r = MCP4XXX::Resolution::res_7bit;
//    MCP4XXX mcp4131(byte CS, p, r, MCP4XXX::WiperConfiguration::potentiometer);*/
//    //pot = new MCP4XXX(CS, MCP4XXX::pot_0, MCP4XXX::res_7bit, MCP4XXX::potentiometer);// , MCP4XXX::Pot::pot_0, MCP4XXX::Resolution::res_7bit, MCP4XXX::WiperConfiguration::potentiometer);
//
//    Board.Delay(1500);
//    Board.InitializeComputerCommunication(9600, "Initializing...");
//    Board.TraceHeader("MCP4131 Digital Potentiometer demo");
//
//    Board.SetPinMode(CS, OUTPUT);
//    SPI.begin();
//    //SPI.setBitOrder(MSBFIRST);
//    //pot = new MCP4XXX(CS);
//
//    Board.Trace(_timeOut.ToString());
//}
//
//// MCP4131_103 10k
//#define POT_RESISTANCE 10000
//#define POT_STEP 128
//
//int digitalPotWrite(int value)
//{
//    double resistance = POT_RESISTANCE - (POT_RESISTANCE / POT_STEP * value);
//    double voltage = 5;
//    double amp = voltage * 1000 / resistance;
//    double power = voltage * amp;
//
//    //word w = pot->get();
//
//    //
//    //digitalWrite(CS, LOW);
//    //byte b1 = SPI.transfer(B00001110); // 14
//    //byte b2 = SPI.transfer(B00000001); // 1
//    //digitalWrite(CS, HIGH);
//
//    //Board.Trace(StringFormat.Format("b1:%d, b2:%d", b1, b2));
//
//
//
//
//
//    byte address = B0000; // pot_0/channel 0
//    byte command_write = B00;
//    byte command_read = B11; // 3
//    byte command_increment = B01;
//    byte command_decrement = B10;
//    byte data_mask = B00000001; // 1
//    byte cmderr_mask = B00000010; // 2
//
//
//    // SET TAP
//    digitalWrite(CS, LOW);
//    byte cmdByte = (address << 4) | (command_write << 2) | cmderr_mask;
//    byte r1 = (cmderr_mask & SPI.transfer(cmdByte)) == 0;
//    byte r2 = SPI.transfer(value);
//    digitalWrite(CS, HIGH);
//    Board.Trace(StringFormat.Format("Digital pot value:%d, Res:%f Ohm, Volt:%f, Amp:%f, Pwr:%f", value, resistance, voltage, amp, power));
//    Board.Trace(StringFormat.Format("cmdByte:%d, r1:%d, r2:%d", cmdByte, r1, r2));
//
//    // READ TAP
//    digitalWrite(CS, LOW);
//    cmdByte = (address << 4) | (command_read << 2) | cmderr_mask | data_mask; // 15
//    r1 = (cmderr_mask & SPI.transfer(0x0F)) == 0; //Read Wiper 0, check error
//    byte Wiper_Reg = SPI.transfer(0xFF); //pull up, value stored in wiper register
//    Board.Trace(StringFormat.Format("cmdByte:%d, r1:%d, Wiper_Reg:%d", cmdByte, r1, Wiper_Reg));
//
//    digitalWrite(CS, HIGH);
//
//}
//
//void loop() {
//
//    int wait = 1250;
//
//    /*   Board.Trace("Starting ");
//    digitalPotWrite(128);
//    delay(1000);
//    return;
//    */
//    for (int i = 0; i <= POT_STEP; i += 16)
//    {
//        digitalPotWrite(i);
//        delay(wait);
//    }
//    for (int i = POT_STEP; i >= 0; i -= 16)
//    {
//        digitalPotWrite(i);
//        delay(wait);
//    }
//}
//
//
///*
//
//STEP VOLT RESISTANCE
//
//16   0.64 1248
//32   1.25 2496
//48   1.67 3744
//64   1.74 4992
//80   1.80 6240
//96   1.87 7488
//112  2.01 8736
//128  3.4  9984
//
//*/