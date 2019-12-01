/*
LiquidCrystal Library - Hello World

Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
library works with all LCD displays that are compatible with the
Hitachi HD44780 driver. There are many of them out there, and you
can usually tell them by the 16-pin interface.

This sketch prints "Hello World!" to the LCD
and shows the time.

The circuit:
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)

Library originally added 18 Apr 2008
by David A. Mellis
library modified 5 Jul 2009
by Limor Fried (http://www.ladyada.net)
example added 9 Jul 2009
by Tom Igoe
modified 22 Nov 2010
by Tom Igoe

This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h>
#include <fArduino.h>

#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);
TimeOut _monitorTimeOut(1000);

// initialize the library with the numbers of the interface pins

//LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


byte smiley[8] = {
    B00000,
    B00100,
    B01110,
    B11111,
    B01110,
    B00100,
    B00000,
};

void setup() {

    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("LCD test");

    Board.SetPinMode(ON_BOARD_LED, OUTPUT);

    _onBoardLed.SetBlinkMode(1000);

    Board.TraceHeader("Init LCD");
    // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);
    lcd.clear();
    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Initializating...");

    lcd.createChar(0, smiley);

    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
        lcd.write(byte(0));
        Board.Delay(300);
    }
    lcd.clear();
    
}

int _counter = 0;

void loop() {

    _onBoardLed.Blink(); // Blink led every 1/2 second

    if (_monitorTimeOut.IsTimeOut()) {
        _counter++;
        lcd.setCursor(0, 0);
        lcd.print(StringFormat.Format("[Counter:%d]", _counter));
    }

    // Process commands coming from the WindowsConsole
    WindowsCommand winCommand = Board.GetWindowsConsoleCommand(); // The WindowsConsole method use the Serial port communication

    if (winCommand.Command == "read") {

        Board.SendWindowsConsoleCommand("Read");
    }
    else if (winCommand.Command == "write") {

        Board.SendWindowsConsoleCommand("Write");
    }
    else {
        if (winCommand.Command != "") {
            Board.SendWindowsConsoleCommand(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
        }
    }
}
