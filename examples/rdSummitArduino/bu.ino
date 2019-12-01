///***********************************************************************
//
//***********************************************************************/
//
//// RFDI RC522
////* Typical pin layout used:
////* -----------------------------------------------------------------------------------------
////*             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
////*             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
////* Signal      Pin          Pin           Pin       Pin        Pin              Pin
////* -----------------------------------------------------------------------------------------
////* RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
////* SPI SS      SDA(SS)      10            53        D10        10               10
////* SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
////* SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
////* SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
//
//
//#include <SPI.h>
//#include <MFRC522.h>
//#include <fArduino.h>
//
//#define ON_BOARD_LED 2
//Led _onBoardLed(ON_BOARD_LED);
//TimeOut _monitorTimeOut(1000);
//
//#define PIR_MOTION_SENSOR_LED 3
//Led _motionSensorLed(PIR_MOTION_SENSOR_LED);
//
//#define PIR_MOTION_SENSOR 4
//#define PIR_MOTION_SENSOR_RESET_TIME 3 * 1000 
//RadioShackPIRSensor _motionSensor(PIR_MOTION_SENSOR);
//
//void setup() {
//
//    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine
//
//    Board.InitializeComputerCommunication(9600, "Initializing...");
//    Board.TraceHeader("R&D Submit Exploration Days PC/Arduino prototype");
//
//    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
//    Board.SetPinMode(PIR_MOTION_SENSOR_LED, OUTPUT);
//    Board.SetPinMode(PIR_MOTION_SENSOR, INPUT);
//
//    // Light the 2 led to signal the system is starting...
//    _motionSensorLed.SetState(true);
//    _onBoardLed.SetState(true);
//    Board.Trace("Initializing...");
//    Board.Delay(1000);
//    _motionSensorLed.SetState(false);
//    _onBoardLed.SetState(false);
//
//    _onBoardLed.SetBlinkMode(1000);
//}
//
//bool _motionDetected = false;
//
//void loop() {
//
//    _onBoardLed.Blink(); // Blink led every 1/2 second
//
//    if (_monitorTimeOut.IsTimeOut()) {
//
//        if (_motionSensor.MotionDetected()) {
//
//            if (!_motionDetected) {
//                Board.Trace("<MotionDetected>");
//                _motionSensorLed.SetState(true);
//                _motionDetected = true;
//            }
//        }
//        else {
//            if (_motionDetected) {
//                _motionDetected = false;
//                _motionSensorLed.SetState(false);
//                Board.Trace("<EndOfMotionDetected>");
//            }
//        }
//    }
//
//    // Process commands coming from the WindowsConsole
//    WindowsCommand winCommand = Board.GetWindowsConsoleCommand(); // The WindowsConsole method use the Serial port communication
//
//    if (winCommand.Command == "read") {
//
//        Board.SendWindowsConsoleCommand("Read");
//    }
//    else if (winCommand.Command == "write") {
//
//        Board.SendWindowsConsoleCommand("Write");
//    }
//    else {
//        if (winCommand.Command != "") {
//            Board.SendWindowsConsoleCommand(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
//        }
//    }
//}
