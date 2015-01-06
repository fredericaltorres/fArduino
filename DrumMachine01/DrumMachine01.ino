/***********************************************************************

Midi Library: https://github.com/FortySevenEffects/arduino_midi_library
    Use SoftwareSerial

Keyboard YPT-210: http://www2.yamaha.co.jp/manual/pdf/emi/english/port/psre213_en_om.pdf

***********************************************************************/

#include "fMidi.h"
#include "MIDI.h"
#include <SoftwareSerial.h>
#include <fArduino.h>

// Pins usage
#if TRINKET
#define ON_BOARD_LED 1
#else
#define ON_BOARD_LED 13
#endif

Led _onBoardLed(ON_BOARD_LED);
boolean _ledState = false;
#define ON_BOARD_LED_NORMAL_BLINKING_RATE 500 // 500 milli-seconds

boolean _playing = false;

#define YPT210_DRUM_CHANNEL 10

// YPT-210 Standard Kit 1
#define BD_SOFT 33
#define BD      36
#define BD_HARD 35
#define SD      38
#define SD_HARD 40
#define HAND_CLAP 39
#define HH_CLOSED 42
#define HH_PEDAL 44
#define HH_OPEN  46
#define CYMBAL_CRASH_1 49
#define CYMBAL_CRASH_2 57
#define CYMBAL_SPLASH 55
#define CYMBAL_CHINESE 52
#define CYMBAL_RIDE_1 51
#define CYMBAL_RIDE_2 59
#define TOM_FLOOR_L 41
#define TOM_FLOOR_H 43
#define TOM_MID_L 47
#define TOM_MID_H 48
#define TOM_HIGH 50
#define TAMBOURINE 54

int _measureCount   = 0;
int tempo           = 120;
int tempo16ms       = 125;
int defaultVelocity = 64;
int _channel        = YPT210_DRUM_CHANNEL;

#define MAX_MEASURES 2
#define MAX_INSTRUMENTS 4

int trackInstrument[MAX_INSTRUMENTS] = { CYMBAL_CRASH_1, BD, SD, HH_CLOSED };
byte measure[MAX_MEASURES][MAX_INSTRUMENTS][16] = {
        {
                                //  1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
            /*CYMBAL_CRASH_1 */ {  75, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
            /*BD             */ { 100, 000, 000, 000, 000, 000, 000, 000, 100, 000, 000, 000, 000, 000, 000, 000 },
            /*SD             */ { 000, 000, 000, 000, 125, 000, 000, 000, 000, 000, 000, 000, 125, 000, 000, 000 },
            /*HH_CLOSED      */ { 100, 000, 100, 000, 100, 000, 100, 000, 100, 000, 100, 000, 100, 000, 100, 000 },
        },
        {
                               //  1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
            /*CYMBAL_CRASH_1 */{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
            /*BD             */{ 100, 000, 000, 000, 000, 000, 000, 000, 100, 000, 000, 000, 000, 000, 000, 000 },
            /*SD             */{ 000, 000, 000, 000, 125, 000, 000, 000, 000, 000, 000, 000, 125, 000,  90, 000 },
            /*HH_CLOSED      */{ 100, 000, 100, 000, 100, 000, 100, 000, 100, 000, 100, 000, 100, 000, 100, 000 },
        },
};

int ComputeVelocity(int v) {

    int vv = (defaultVelocity * v) / 100;
    if (vv >= 128)
        vv = 127;
    if (vv < 0)
        vv = 0;
    return vv;
}

SoftwareSerial _softwareSerial(2, 3);
MIDI_CREATE_INSTANCE(HardwareSerial, _softwareSerial, MIDI); 

void setup() {
    
    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Drum Machine 01");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(ON_BOARD_LED_NORMAL_BLINKING_RATE);
    _softwareSerial.begin(31250);
    MIDI.begin();
    Board.Trace(StringFormat.Format("Playing _channel:%d", _channel));
}

void loop() {

    _onBoardLed.Blink(); // Blink led every 1/2 second

    if (_playing) {
        
        for (int m = 0; m < MAX_MEASURES; m++) {

            for (int m16 = 0; m16 < 16; m16++) {

                for (int it = 0; it < MAX_INSTRUMENTS; it++) {
                    if (measure[it][m16] > 0) {
                        MIDI.sendNoteOn(trackInstrument[it], ComputeVelocity(measure[m][it][m16]), _channel);
                    }
                }
                Board.Delay(tempo16ms);
                for (int it = 0; it < MAX_INSTRUMENTS; it++) {
                    if (measure[m][it][m16] == 1) {
                        MIDI.sendNoteOff(trackInstrument[it], 0, _channel);
                    }
                }
            }
        }
    }

    WindowsCommand winCommand = Board.GetWindowsConsoleCommand(); // The WindowsConsole method use the Serial port communication

    if (winCommand.Command == "play") {

        _playing = !_playing;
        Board.SendWindowsConsoleCommand(StringFormat.Format("_playing:%b", _playing));
    }   
    else {
        if (winCommand.Command != "") {
            Board.SendWindowsConsoleCommand(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
        }
    }
}



//for (byte note = 30; note < 90; note++) {
//    _onBoardLed.Blink(); // Blink led every 1/2 second
//    MIDI.sendNoteOn(note, 64, _channel);
//    delay(100);
//    MIDI.sendNoteOff(note, 0, _channel);
//    delay(10);
//}
