///************************************
//Program to run on an Arduino or Trinket Control
//
//http://www.arduino.cc/en/Tutorial/ShiftOut
//
//*/
//
//#include "fArduino.h"
//
////#define ARDUINO_UNO 1
////#define TRINKET 1
//#define TRINKET_PRO 1
//
//#if defined(ARDUINO_UNO)
//int OUPUT_PIN[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
//#endif
//#if defined(TRINKET_PRO)
//// Trinket Pro has no output pin 2 and 7
//int OUPUT_PIN[] = { 3, 4, 5, 6, 8, 9, 10, 11, 12, 13 };
//#endif
//#if defined(TRINKET)
//// On a trinket to test pin 3 and 4 the USB cable must be disconnected
//int OUPUT_PIN[] = { 0, 1, 2 }; // , 3, 4 
//#endif
//
//int _outputPinIndex = 0;
//
//boolean _outputPinState;
//
//#if defined(TRINKET)
//#define ON_BOARD_LED 1
//#else
//#define ON_BOARD_LED 13
//#endif
//
//Led _onBoardLed(ON_BOARD_LED);
//
//int GetCurrentPin() {
//
//    return OUPUT_PIN[_outputPinIndex];
//}
//void ShowUserInfo() {
//
//#if !TRINKET // Eliminate a lot of binary, smaller exe
//    Board.Trace(StringFormat.Format("new Led pin:%d, on:%b", GetCurrentPin(), _outputPinState));
//#endif
//}
//void setup() {
//
//#if !TRINKET
//    Board.Delay(1000); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole
//#endif
//
//    Board.InitializeComputerCommunication(9600, "Initializing...");
//    Board.TraceHeader("MicroController Test");
//
//    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
//
//    Board.SetPinMode(GetCurrentPin(), OUTPUT);
//    _onBoardLed.SetBlinkMode(500);
//    ShowUserInfo();
//}
//void PreviousOutputPin() {
//
//    _outputPinState = false;
//    Board.LedOn(GetCurrentPin(), _outputPinState);
//
//    _outputPinIndex--;
//    if (_outputPinIndex < 0)
//        _outputPinIndex = 0;
//
//    Board.SetPinMode(GetCurrentPin(), OUTPUT);
//    ShowUserInfo();
//}
//void NextOutputPin() {
//
//    _outputPinState = false;
//    Board.LedOn(GetCurrentPin(), _outputPinState);
//
//    _outputPinIndex++;
//    if (_outputPinIndex == ArraySize(OUPUT_PIN)) {
//        _outputPinIndex = 0;
//    }
//    Board.SetPinMode(GetCurrentPin(), OUTPUT);
//    ShowUserInfo();
//}
//void TestPWMCurrentPin() {
//
//    _outputPinState = false;
//    Board.LedOn(GetCurrentPin(), _outputPinState);
//
//    for (int i = 0; i < 250; i += 50) {
//        Board.Trace(StringFormat.Format("Led pin:%d, PWM level:%d", GetCurrentPin(), i));
//        Board.LedSet(GetCurrentPin(), i);
//        Board.Delay(100);
//    }
//    for (int i = 250; i > 0; i -= 50) {
//        Board.Trace(StringFormat.Format("Led pin:%d, PWM level:%d", GetCurrentPin(), i));
//        Board.LedSet(GetCurrentPin(), i);
//        Board.Delay(100);
//    }
//    Board.LedOn(GetCurrentPin(), _outputPinState);
//}
//void ReverseCurrentPin() {
//
//    _outputPinState = !_outputPinState;
//    Board.Trace(StringFormat.Format("Led pin:%d, state:%b", GetCurrentPin(), _outputPinState));
//    Board.LedOn(GetCurrentPin(), _outputPinState);
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////
//// Because the trinklet has no serial interface, we just loop around the pin 0, 1, 2
//// or 0, 1, 2, 4, 5 and light a led
//void TrinketLoop() {
//
//    _onBoardLed.Blink();
//
//    Board.LedOn(GetCurrentPin(), true);
//    Board.Delay(150);
//    Board.LedOn(GetCurrentPin(), false);
//    Board.Delay(150);
//    NextOutputPin();
//}
//
//void ArduinoAndTrinketProLoop() {
//
//#if TRINKET
//    TrinketLoop(); return;
//#endif
//
//    _onBoardLed.Blink();
//
//    boolean executed = false;
//
//    WindowsCommand winCommand = Board.GetWindowsConsoleCommand();
//
//    if (winCommand.Command != "") {
//
//        if (winCommand.Command == "testOut") {
//
//            ReverseCurrentPin();
//            executed = true;
//        }
//        else if (winCommand.Command == "testOutPWM") {
//
//            TestPWMCurrentPin();
//            executed = true;
//        }
//        else if (winCommand.Command == "incPin") {
//
//            NextOutputPin();
//            executed = true;
//        }
//        else if (winCommand.Command == "decPin") {
//
//            PreviousOutputPin();
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
//
//void loop() {
//
//#if TRINKET
//    TrinketLoop();
//#else
//    ArduinoAndTrinketProLoop();
//#endif
//}
