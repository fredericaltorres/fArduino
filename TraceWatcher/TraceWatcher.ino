/*************************************************************************

TraceWatcher 

A red, yellow, green USB programmable device.

Programmable from Windows and C#

- Proto 1 use an Arduino and Serial port to communicate with device
- Proto 2 will use the Adafruit FT232H Breakout 

    https://www.adafruit.com/products/2264 $15    

***************************************************************************/

#include "fArduino.h"

// Pins Usage

#define RED_LED_ONBAORD_PIN     13

#define RED_LED_PIN             3 // Yellow wire
#define YELLOW_LED_PIN          4 // Blue wire
#define GREEN_LED_PIN           5 // Blue wire

// Define music to start or stop something
#define FACTOR 4
int musicStart[] = { NOTE_E4, 8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_A4, 8 * FACTOR, NOTE_B4, 8 * (FACTOR / 2) };
int musicEnd[] = { NOTE_B4, 8 * FACTOR, NOTE_A4, 8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_E4, 8 * (FACTOR / 2) };

Led _onBoardLed(RED_LED_ONBAORD_PIN);
Led _redLed = Led(RED_LED_PIN);
Led _yellowLed = Led(YELLOW_LED_PIN);
Led _greenLed  = Led(GREEN_LED_PIN);

void PowerOff() {

    _redLed.SetState(false);
    _yellowLed.SetState(false);
    _greenLed.SetState(false);
}

void setup() {

    Board.Delay(1500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("TraceWatcher initializing...");

    Board.SetPinMode(RED_LED_PIN, OUTPUT);
    Board.SetPinMode(YELLOW_LED_PIN, OUTPUT);
    Board.SetPinMode(GREEN_LED_PIN, OUTPUT);
    Board.SetPinMode(RED_LED_ONBAORD_PIN, OUTPUT);

    PowerOff();
    _onBoardLed.SetBlinkMode(1000);

    Board.Trace("Ready");
}

void loop() {

    _onBoardLed.Blink(); // Blink every seconds

    WindowsCommand winCommand = Board.GetWindowsConsoleCommand();
    boolean executed = true;

    if (winCommand.Command != "") {

        if (winCommand.Command == "redOn") {

            _redLed.SetState(true);
        }
        else if (winCommand.Command == "redOff") {

            _redLed.SetState(false);
        }
        else if (winCommand.Command == "yellowOn") {

            _yellowLed.SetState(true);
        }
        else if (winCommand.Command == "yellowOff") {

            _yellowLed.SetState(false);
        }
        else if (winCommand.Command == "greenOn") {

            _greenLed.SetState(true);
        }
        else if (winCommand.Command == "greenOff") {

            _greenLed.SetState(false);
        }

        /*if (executed) {
            Board.Trace(StringFormat.Format("[%s executed]", winCommand.Command.c_str()));
        }
        else {
            Board.Trace(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
        }*/
    }
}
