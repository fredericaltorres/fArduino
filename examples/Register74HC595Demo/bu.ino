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
//int latchPin = 8;   // Pin connected to ST_CP of 74HC595
//int clockPin = 12;  // Pin connected to SH_CP of 74HC595
//int dataPin = 11;  // Pin connected to DS of 74HC595
//
//#define ON_BOARD_LED 13
//Led _onBoardLed(ON_BOARD_LED);
//
//void Register74HC595_SendValue(int v) {
//
//    // take the latchPin low so  the LEDs don't change while you're sending in bits:
//    digitalWrite(latchPin, LOW);
//    shiftOut(dataPin, clockPin, MSBFIRST, v); // shift out the bits:
//    digitalWrite(latchPin, HIGH); //take the latch pin high so the LEDs will light up:
//}
//
//void setup() {
//
//    Board.Delay(1500); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole
//
//    Board.InitializeComputerCommunication(9600, "Initializing...");
//    Board.TraceHeader("Register74HC595 Demo");
//    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
//    _onBoardLed.SetBlinkMode(500);
//
//    //set pins to output so you can control the shift register
//    Board.SetPinMode(latchPin, OUTPUT);
//    Board.SetPinMode(clockPin, OUTPUT);
//    Board.SetPinMode(dataPin, OUTPUT);
//
//    Register74HC595_SendValue(0);
//}
//
//void ShowUserData(int value) {
//
//    Board.SendWindowsConsoleCommand(StringFormat.Format("value:%d", value), true, true);
//}
//
//void DisplayValueFrom1To64() {
//
//    for (int v = 0; v < 64; v++) {
//
//        Register74HC595_SendValue(v);
//        ShowUserData(v);
//        delay(500);
//    }
//    Register74HC595_SendValue(0);
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
//            executed = true;
//        }
//        else if (winCommand.Command == "loop64") {
//
//            DisplayValueFrom1To64();
//            executed = true;
//        }
//        else if (winCommand.Command == "reset") {
//
//            Register74HC595_SendValue(0);
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
