/************************************

    http://arduino.cc/en/Reference/HomePage

    http://playground.arduino.cc/Interfacing/Csharp
    http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging

    TV for $1 - https://www.youtube.com/watch?v=WlBXiZpuncg

*/

#include "fArduino.h"

#define ON_BOARD_LED 13
boolean _ledState = false;
unsigned long _counter = 0;
Led _onBoardLed(ON_BOARD_LED);

void setup() {

    Board.Delay(1500); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Serial Communicator **");   
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(1000);
}

void PowerLed(boolean state) {

    Board.LedOn(ON_BOARD_LED, state);
}

void ShowUserData() {

    Board.SendWindowsConsoleCommand(StringFormat.Format("counter:%ul", _counter));
}

void loop() {
    
    _onBoardLed.Blink();
    _counter++;

    boolean executed          = false;
    WindowsCommand winCommand = Board.GetWindowsConsoleCommand();
    
    if (winCommand.Command != "") {

        if (winCommand.Command == "test") {

            executed = true;
        }
        else if (winCommand.Command == "getData") {

            ShowUserData();
            executed = true;
        }
        else if (winCommand.Command == "resetData") {

            _counter = 0;
            ShowUserData();
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
