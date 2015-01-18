/**************************************************************************

This is a demo for the Adafruit MCP9808 breakout
http://www.adafruit.com/products/1782

*************************************************************************/

#include "fArduino.h"

//#define SPEAKER_ON
#define SPEAKER_PIN 8

#if SPEAKER_ON
SpeakerManager _speakerManager(SPEAKER_PIN);
#endif

// Define music to start or stop something
#define FACTOR 4
int musicStart[] = { NOTE_E4, 8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_A4, 8 * FACTOR, NOTE_B4, 8 * (FACTOR / 2) };
int musicEnd[]   = { NOTE_B4, 8 * FACTOR, NOTE_A4, 8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_E4, 8 * (FACTOR / 2) };

#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);

TimeOut _timeOut(250);

#define PIR_MOTION_SENSOR 2
#define PIR_MOTION_SENSOR_RESET_TIME 4 * 1000 
RadioShackPIRSensor _motionSensor(PIR_MOTION_SENSOR);

void NotifyUserAppIsReady() {
    #if SPEAKER_ON
    _speakerManager.PlaySequence(ArraySize(musicStart), musicStart);
    Board.Delay(200);
    _speakerManager.PlaySequence(ArraySize(musicEnd), musicEnd);
    #endif
}

void setup() {

    Board.Delay(1500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("RadioShack PIR Sensor - Motion Sensor");

    Board.SetPinMode(ON_BOARD_LED,      OUTPUT);
    Board.SetPinMode(PIR_MOTION_SENSOR, INPUT);
    #if SPEAKER_ON
    Board.SetPinMode(SPEAKER_PIN,       OUTPUT);
    #endif
    
    _onBoardLed.SetBlinkMode(1000);

    Board.Trace(_timeOut.ToString());
    NotifyUserAppIsReady();
}

void loop() {

    _onBoardLed.Blink();

    if (_timeOut.IsTimeOut()) {

        if (_motionSensor.MotionDetected()) {
                        
            Board.Trace("Motion Detected");
            _onBoardLed.SetState(true);

            #if SPEAKER_ON
            _speakerManager.PlaySequence(ArraySize(musicStart), musicStart);
            Board.Delay(PIR_MOTION_SENSOR_RESET_TIME);
            _speakerManager.PlaySequence(ArraySize(musicEnd), musicEnd);
            #else
            Board.Delay(PIR_MOTION_SENSOR_RESET_TIME);
            #endif

            Board.Trace("Ready");
            _onBoardLed.SetState(false);
        }
    }
}