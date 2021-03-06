/***********************************************************************

Midi Library: https://github.com/FortySevenEffects/arduino_midi_library
Use SoftwareSerial

Keyboard YPT-210: http://www2.yamaha.co.jp/manual/pdf/emi/english/port/psre213_en_om.pdf

http://arduino.cc/en/Reference/HomePage

Pieze Sensor:
    https://www.sparkfun.com/datasheets/Sensors/Flex/MSI-techman.pdf

***********************************************************************/

#include "MIDI.h"
#include <SoftwareSerial.h>
#include <fArduino.h>

// Pins usage
#define ON_BOARD_LED 13
#define MIDI_IN_PIN  2
#define MIDI_OUT_PIN 3
#define PIEZO_1_PIN  0

Led _onBoardLed(ON_BOARD_LED);
boolean _ledState = false;

SoftwareSerial _softwareSerial(MIDI_IN_PIN, MIDI_OUT_PIN);
MIDI_CREATE_INSTANCE(HardwareSerial, _softwareSerial, MIDI);

#define YPT210_DRUM_CHANNEL 10

// YPT-210 Standard Kit 1, Midi note
#define BD_SOFT             33
#define BD                  36
#define BD_HARD             35
#define SD                  38
#define SD_HARD             40
#define HAND_CLAP           39
#define HH_CLOSED           42
#define HH_PEDAL            44
#define HH_OPEN             46
#define CYMBAL_CRASH_1      49
#define CYMBAL_CRASH_2      57
#define CYMBAL_SPLASH       55
#define CYMBAL_CHINESE      52
#define CYMBAL_RIDE_1       51
#define CYMBAL_RIDE_2       59
#define TOM_FLOOR_L         41
#define TOM_FLOOR_H         43
#define TOM_MID_L           47
#define TOM_MID_H           48
#define TOM_HIGH            50
#define TAMBOURINE          54

int     _channel = YPT210_DRUM_CHANNEL;

void setup() {

    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Finger Drummer");

    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(500);

    _softwareSerial.begin(31250);
    MIDI.begin();

    Board.Trace(StringFormat.Format("Playing _channel:%d", _channel));
}

void ShowUserInfo() {

    Board.SendWindowsConsoleCommand(StringFormat.Format("user info"), false, true);
}

void TestMidi(int channel) {

    for (byte note = 30; note < 90; note++) {

        MIDI.sendNoteOn(note, 64, channel);
        delay(20);
        MIDI.sendNoteOff(note, 0, channel);
        delay(5);
    }
}
void ProcessWindowsConsoleCommand() {

    if (Serial.available()) {

        WindowsCommand winCommand = Board.GetWindowsConsoleCommand(); // The WindowsConsole method use the Serial port communication
        if (winCommand.Command == "testMidi") {
            TestMidi(1);
            TestMidi(10);
        }
        else {
            if (winCommand.Command != "") {
                Board.SendWindowsConsoleCommand(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()), false, true);
            }
        }
    }
}


#define PIEZOTHRESHOLD 10
#define HITHAT_MAX_VALUE 250
#define SD_MAX_VALUE 1000
#define BD_MAX_VALUE 1000

Piezo fingerHitHat  (1, PIEZOTHRESHOLD, HITHAT_MAX_VALUE, 127);
Piezo fingerHitHat2 (2, PIEZOTHRESHOLD, HITHAT_MAX_VALUE, 127);
Piezo fingerSD      (3, PIEZOTHRESHOLD, SD_MAX_VALUE, 90);
Piezo fingerBD      (0, PIEZOTHRESHOLD, BD_MAX_VALUE, 100);


void loop() {

    String buf("");
    _onBoardLed.Blink();

    /// http://todbot.com/arduino/sketches/midi_drum_kit/midi_drum_kit.pde

    int v1 = fingerHitHat.GetValue();
    if (v1 != -1) {
        MIDI.sendNoteOn(HH_CLOSED, v1, _channel);
    }

    v1 = fingerHitHat2.GetValue();
    if (v1 != -1) {
        MIDI.sendNoteOn(HH_CLOSED, v1, _channel);
    }

    v1 = fingerSD.GetValue();
    if (v1 != -1) {
        MIDI.sendNoteOn(SD_HARD, v1, _channel);
    }

    v1 = fingerBD.GetValue();
    if (v1 != -1) {
        MIDI.sendNoteOn(BD, v1, _channel);
        MIDI.sendNoteOn(HH_CLOSED, v1 - (v1*20/100), _channel);
    }

    ProcessWindowsConsoleCommand();
}



//for (byte note = 30; note < 90; note++) {
//    _onBoardLed.Blink(); // Blink led every 1/2 second
//    MIDI.sendNoteOn(note, 64, _channel);
//    delay(100);
//    MIDI.sendNoteOff(note, 0, _channel);
//    delay(10);
//}
