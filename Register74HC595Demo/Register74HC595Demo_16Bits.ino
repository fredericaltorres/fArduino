//
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
//// Pin connected to latch pin (ST_CP, Storage Register Clock Pin) of 74HC595 - Register pin 12
//const int latchPin = 8; // Green Wire
//
//// Pin connected to clock pin (SH_CP, Shift Register Clock Pin) of 74HC595 - Register pin 11
//const int clockPin = 12;  // Yellow wire
//
//// Pin connected to Data in (DS) of 74HC595  - Register pin 14
//const int dataPin = 11; // Blue wire
//
//Register74HC595_16Bit _register74HC595_16Bit(latchPin, clockPin, dataPin);
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
//    _onBoardLed.SetBlinkMode(500);
//    _register74HC595_16Bit.Send16BitValue(0);
//}
//
//void ShowUserData(int value) {
//
//    Board.SendWindowsConsoleCommand(StringFormat.Format("value:%d", value), true, true);
//}
//
//
//void Animations() {
//
//    int waitTime = 125;
//    _register74HC595_16Bit.AnimateOneLeftToRightAndRightToLeft2Leds(waitTime, 3);
//
//    waitTime = 100;
//    _register74HC595_16Bit.AnimateOneLeftToRightAndRightToLeft1Leds(waitTime, 2);
//}
//
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
//            Board.Trace("Start Animations");
//            Animations();
//            Board.Trace("End Animations");
//            executed = true;
//        }
//        else if (winCommand.Command == "reset") {
//
//            _register74HC595_16Bit.Send16BitValue(0);
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
