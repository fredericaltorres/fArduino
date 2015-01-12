/************************************

Serial to Parallel Shifting-Out with a 74HC595
How to handle 8 leads with only 3 pins

http://www.arduino.cc/en/Tutorial/ShiftOut

http://blog.rastating.com/using-a-74hc595-shift-register-with-an-arduino-uno/

http://arduino.cc/en/Reference/HomePage

http://playground.arduino.cc/Interfacing/Csharp
http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging

TV for $1 - https://www.youtube.com/watch?v=WlBXiZpuncg

*/

#include "fArduino.h"

int latchPin = 8;   // Pin connected to ST_CP of 74HC595
int clockPin = 12;  // Pin connected to SH_CP of 74HC595
int dataPin = 11;  // Pin connected to DS of 74HC595

Register74HC595 _register74HC595(latchPin, clockPin, dataPin);

#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);

void setup() {

    Board.Delay(1500); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Register74HC595 Demo");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(500);
}

void ShowUserData(int value) {

    Board.SendWindowsConsoleCommand(StringFormat.Format("value:%d", value), true, true);
}

void DisplayValueFrom1To64() {

    for (int v = 0; v < 64; v++) {

        _register74HC595.SendValue(v);
        ShowUserData(v);
        delay(500);
    }
    _register74HC595.SendValue(0);
}


int p2[] = { 1 , 2, 4 , 8, 16, 32, 64, 128 };

void DisplayValueFrom0To8() {

    int waitTime = 250;
    Board.Trace("FlashValue");
    _register74HC595.FlashValue(255, 4, waitTime);

    waitTime = 65;
    Board.Trace("AnimateOneLeftToRightAndRightToLeft");
    _register74HC595.AnimateOneLeftToRightAndRightToLeft(waitTime);

    Board.Trace("AnimateAllLeftToRight");
    _register74HC595.AnimateAllLeftToRight(waitTime);

    Board.Trace("AnimateAllLeftToRight");
    _register74HC595.AnimateAllRightToLeft(waitTime);

    _register74HC595.SendValue(0);
}

void loop() {

    _onBoardLed.Blink();

    boolean executed = false;
    WindowsCommand winCommand = Board.GetWindowsConsoleCommand();

    if (winCommand.Command != "") {

        if (winCommand.Command == "test") {

            executed = true;
        }
        else if (winCommand.Command == "loop64") {

            DisplayValueFrom1To64();
            executed = true;
        }
        else if (winCommand.Command == "loop8") {

            DisplayValueFrom0To8();
            executed = true;
        }
        else if (winCommand.Command == "reset") {

            _register74HC595.SendValue(0);
            executed = true;
        }
        if (executed) {
            Board.Trace(StringFormat.Format("[%s executed]", winCommand.Command.c_str()));
        }
        else {
            Board.Trace(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
        }
    }
}
