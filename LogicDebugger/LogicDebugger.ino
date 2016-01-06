/*

*/

#include <fArduino.h>

#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);
TimeOut _monitorTimeOut(1000);

#define ANALYSED_CLOCK_PIN  2
#define LED_CLOCK_PIN       3
#define TRIGGER_CLOCK_PIN   12
PinLogicAnalyser clockLogicAnalyser(ANALYSED_CLOCK_PIN, LED_CLOCK_PIN);

#define ANALYSED_SDA_PIN  7
#define LED_SDA_PIN       6
#define TRIGGER_SDA_PIN   11
PinLogicAnalyser sdaLogicAnalyser(ANALYSED_SDA_PIN, LED_SDA_PIN);

void setup() {

    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Logic Debugger -- Analyse pin 2 as clock");

    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    Board.SetPinMode(TRIGGER_CLOCK_PIN, OUTPUT);
    Board.SetPinMode(TRIGGER_SDA_PIN, OUTPUT);

    _onBoardLed.SetBlinkMode(1000);
}

void loop() {

    _onBoardLed.Blink(); // Blink led every 1/2 second
    clockLogicAnalyser.Process();
    sdaLogicAnalyser.Process();

    // Process commands coming from the WindowsConsole
    WindowsCommand winCommand = Board.GetWindowsConsoleCommand(); // The WindowsConsole method use the Serial port communication

    if (winCommand.Command == "clock") {

        Board.LedOn(TRIGGER_CLOCK_PIN, !clockLogicAnalyser.State);
        Board.SendWindowsConsoleCommand(StringFormat.Format("Led clock:%d", clockLogicAnalyser.State));
    }
    else if (winCommand.Command == "data") {    

        Board.LedOn(TRIGGER_SDA_PIN, !sdaLogicAnalyser.State);
        Board.SendWindowsConsoleCommand(StringFormat.Format("Led data:%d", sdaLogicAnalyser.State));
    }
    else {
        if (winCommand.Command != "") {
            Board.SendWindowsConsoleCommand(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
        }
    }
}
