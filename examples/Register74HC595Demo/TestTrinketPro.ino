///************************************
//
//Serial to Parallel Shifting-Out with a 74HC595
//How to handle 8 leads with only 3 pins
//
//http://www.arduino.cc/en/Tutorial/ShiftOut
//
//http://blog.rastating.com/using-a-74hc595-shift-register-with-an-arduino-uno/
//
//http://arduino.cc/en/Reference/HomePage
//
//http://playground.arduino.cc/Interfacing/Csharp
//http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging
//
//TV for $1 - https://www.youtube.com/watch?v=WlBXiZpuncg
//
//*/
//
//#include "fArduino.h"
//
//
//// Pin connected to clock pin (SH_CP, Shift Register Clock Pin) of 74HC595 - Register pin 11
//int PIN = 4;  // Yellow wire
//
//boolean _ledPin12State;
//
//#define ON_BOARD_LED 13
//Led _onBoardLed(ON_BOARD_LED);
//
//void setup() {
//
//    Board.Delay(1000); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole
//
//    Board.InitializeComputerCommunication(9600, "Initializing...");
//    Board.TraceHeader("Register74HC595 Demo");
//    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
//    Board.SetPinMode(PIN, OUTPUT);
//    _onBoardLed.SetBlinkMode(500);
//}
//
//void ShowUserData(int value) {
//
//    Board.SendWindowsConsoleCommand(StringFormat.Format("value:%d", value), true, true);
//}
//
//void loop() {
//
//    _onBoardLed.Blink();
//
//    boolean executed = false;
//    WindowsCommand winCommand = Board.GetWindowsConsoleCommand();
//
//    if (winCommand.Command != "") {
//
//        if (winCommand.Command == "test") {
//
//            Board.Trace("Tested");
//            executed = true;
//        }
//        else if (winCommand.Command == "test") {
//
//            executed = true;
//        }
//        else if (winCommand.Command == "loop64") {
//
//            executed = true;
//        }
//        else if (winCommand.Command == "animations") {
//
//            _ledPin12State = !_ledPin12State;
//            Board.Trace(StringFormat.Format("Led pin:%d, state:%b", PIN, _ledPin12State));
//            Board.LedOn(PIN, _ledPin12State);
//            executed = true;
//        }
//        else if (winCommand.Command == "incPin") {
//
//            PIN++;
//            if (PIN == 7)
//                PIN = 8;
//            Board.Trace(StringFormat.Format("new Led pin:%d", PIN));
//            Board.SetPinMode(PIN, OUTPUT);
//            executed = true;
//        }
//        else if (winCommand.Command == "decPin") {
//
//            PIN--;
//            if (PIN == 7)
//                PIN = 6;
//            Board.Trace(StringFormat.Format("new Led pin:%d", PIN));
//            Board.SetPinMode(PIN, OUTPUT);
//            executed = true;
//        }
//        if (executed) {
//            Board.Trace(StringFormat.Format("[%s executed]", winCommand.Command.c_str()));
//        }
//        else {
//            Board.Trace(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
//        }
//    }
//}
