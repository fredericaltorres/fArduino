/************************************

    Cheap Hc-sr04
    http://www.amazon.com/gp/product/B0089VA3AY/ref=as_li_qf_sp_asin_il_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B0089VA3AY&linkCode=as2&tag=wwwrandomnerd-20

*/


#include "fArduino.h"

#define ON_BOARD_LED 13
boolean _ledState = false; 
unsigned long _counter = 0;
Led _onBoardLed(ON_BOARD_LED);

#define trigPin 11
#define echoPin 12


void setup() {

    Board.Delay(1500); // Wait one second so after plug in the USB port, I can start the ArduinoWindowsConsole

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Serial Communicator With EEPROM");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(1000);

    Board.SetPinMode(trigPin, OUTPUT);
    Board.SetPinMode(echoPin, INPUT);    
}

void PowerLed(boolean state) {

    Board.LedOn(ON_BOARD_LED, state);
}

void ShowUserData() {

    Board.SendWindowsConsoleCommand(StringFormat.Format("counter:%ul", _counter));
}


long previousDistance = -1;

UltrasonicDistanceSensor ultrasonicDistanceSensor(trigPin, echoPin);

void loop() {

    Board.Delay(100);
    
    //long duration, distance;
    //digitalWrite(trigPin, LOW);  // Added this line
    //delayMicroseconds(2); // Added this line
    //digitalWrite(trigPin, HIGH);
    ////  delayMicroseconds(1000); - Removed this line
    //delayMicroseconds(10); // Added this line
    //digitalWrite(trigPin, LOW);
    //duration = pulseIn(echoPin, HIGH);
    //distance = (duration / 2) / 29.1;

    int distance = ultrasonicDistanceSensor.Ping();

    if (previousDistance != distance) {
        if (distance < 1000) {
            Board.Trace(StringFormat.Format("distance:%d", distance));
        }
        previousDistance = distance;
    }
    
    _onBoardLed.Blink();
    _counter++;

    boolean executed = false;
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
