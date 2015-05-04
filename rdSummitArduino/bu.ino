///***********************************************************************
//
//Acquiring and storing temperature with Arduino and a DS18B20 sensor
//
//- Acquiring temperature data every 6 minutes.
//- Store the data into an EPROM Array. Sore 3 days of data on 512 bytes of EPROM.
//- Api to communicate with a Windows Console to
//- resetData
//- getData: Send acquired data as CSV to the WindowsConsole (Serial port)
//- acquireData
//- Use fArduino library to write clean and readable code
//
//- User interface on the arduino:
//Use on board led, to express that the application state:
//1) if blinking on/off every 1/2 second, the application is waiting, normal state
//2) if blinking on/off for 1.6 second quickly, the application just acquire a new temperature
//3) if blinking on/off for 4 seconds semi-quickly repeatedly, There is an issue with the sensor
//
//***********************************************************************/
//
//
//#include <MFRC522.h>
//#include <fArduino.h>
//
//#define ON_BOARD_LED 13
//Led _onBoardLed(ON_BOARD_LED);
//TimeOut _monitorTimeOut(1000);
//
//#define PIR_MOTION_SENSOR_LED 12
//Led _motionSensorLed(PIR_MOTION_SENSOR_LED);
//
//#define PIR_MOTION_SENSOR 11
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
