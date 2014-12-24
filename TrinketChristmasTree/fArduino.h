// fArduino.h

#ifndef _FARDUINO_h
#define _FARDUINO_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ArraySize(x) sizeof(x) / sizeof(x[0])
#define UNDEFINED_PIN -1

#define MAX_FORMAT_SIZE 128

//////////////////////////////////////////////////////
/// Represet the Trinket/Arduino board
///
class BoardClass {
private:
    boolean _serialCommunicationInitialized;
    unsigned long _startTime;
protected:
public:
    BoardClass();
    ~BoardClass();

    char * GetTime();
    String Format(char *format, ...);
    int GetFreeMemory();

    boolean GetButtonStateDebounced(int pin, boolean lastState);
    void LedOn(int pin, boolean state);
    void LedOn(int pin, boolean state, int delay);
    void LedSet(int pin, int level);
    void SetPinMode(uint8_t, uint8_t);
    void Delay(unsigned long);

    void InitializeComputerCommunication(unsigned long speed, char * message);
    void Trace(char * msg);
    void Trace(const char * msg);
    void Trace(String msg);
    void TraceHeader(char * msg);
    void TraceFormat(char * format, int d1);
    void TraceFormat(char * format, int d1, int d2);
    void TraceFormat(char * format, char *s);
    void TraceFormat(char * format, char *s1, char *s2);
    void TraceFormat(char * format, char *s1, char *s2, char * s3);
    void TraceFormat(char * format, char d1);
    void TraceFormat(char * format, float f1);
    void TraceFormat(char * format, double f1, double f2);

    void ClearKeyboard();

    //char * ToString(double d);
    //char * ToString(float f);
};

// Global Signleton
extern BoardClass Board;


//////////////////////////////////////////////////////
/// Led
///
class Led {
private:
    int _pin;
    unsigned long _rate;
    boolean _state;
    int _level;
    unsigned long _blinkStartTime;
protected:
public:

    bool State;
    Led(int pin);
    void SetState(boolean on);
    void SetLevel(int level);
    ~Led();
    void SetBlinkMode(unsigned long rate);
    unsigned long GetBlinkDurationCycle();
    void SetBlinkModeOff();
    boolean IsBlinking();
    void Blink();
};

//////////////////////////////////////////////////////
/// MultiState Button
///
class MultiStateButton {

private:
    int         _pin;
    int         _previousPin;
    int         _maxState;
    const int  *_ledIntensityArray;  // Point to an array of int mapping the intensity of the led with the StateIndex
    bool        _statedChanged;

public:
    Led     *LedInstance;
    int     StateIndex;

    boolean NextButtonLastStateInLoop;
    boolean PreviousButtonLastStateInLoop;

    MultiStateButton(int pin, Led * led, int maxState, const int * ledIntensityArray);
    ~MultiStateButton();

    boolean GetButtonStateDebounced();
    boolean GetPreviousButtonStateDebounced();
    void NextState();
    void PreviousState();
    void UpdateUI();
    void SetPreviousButton(int pin);

    boolean StateChangeFor(int state);



};

#endif

//////////////////////////////////////////////////////
/// TimeOut
///
class TimeOut {
private:
    unsigned long _time;
    unsigned long _duration;
public:
    unsigned long Counter;

    TimeOut(unsigned long duration);
    ~TimeOut();
    void Reset();
    boolean IsTimeOut();
    boolean EveryCalls(unsigned long callCount);
};


//////////////////////////////////////////////////////
///  Temperature Manager
///
class TemperatureManager {
private:
public:
    TemperatureManager();
    ~TemperatureManager();
    float CelsiusToFahrenheit(float celsius);
    void Add(float celsius);
};


// Speaker Notes
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define NOTE_SILENCE 0

#define SPEAKERMANAGER_PLAY_SEQUENCE_NORMAL 1
#define SPEAKERMANAGER_PLAY_SEQUENCE_SLOW   2
#define SPEAKERMANAGER_PLAY_SEQUENCE_REVERSE true

#define _2_NOTE 1
#define _2_NOTE 2
#define _4_NOTE 4
#define _8_NOTE 8

/**************************************************
SpeakerManager

based on http://www.instructables.com/id/Arduino-Basics-Making-Sound/step2/Playing-A-Melody/
http://makezine.com/projects/make-35/advanced-arduino-sound-synthesis/

Remark from Jeremy Blum about using the default Arduino tone() method
http://www.jeremyblum.com/2010/09/05/driving-5-speakers-simultaneously-with-an-arduino
The built-in tone() function allows you to generate a squarewave with 50% duty cycle of your
selected frequency on any pin on the arduino.
It relies on one of the arduino’s 3 timers to work in the background.

SPECIFICALLY, IT USES TIMER2, WHICH IS ALSO RESPONSIBLE FOR
CONTROLLING PWM ON PINS 3 AND 11.
SO YOU NATURALLY LOOSE THAT ABILITY WHEN USING THE TONE() FUNCTION.

*/
class SpeakerManager {
private:
    byte _pin;

    int           _backGroundNoteDurationIndex;
    int *         _backGroundNoteDurationSequence;
    int           _backGroundNoteDurationSequenceSize;
    

public:
    boolean       BackGroundOn;

    SpeakerManager(byte pin);
    ~SpeakerManager();
    void Play(int note, int duration);
    void Play(int note, int duration, int speed);
    void Play(int note, int duration, int speed, boolean stop);
    void Off();
    void PlaySequence(int size, int * noteDurationSequence);
    void PlaySequence(int size, int * noteDurationSequence, int speed);
    void PlaySequence(int size, int * noteDurationSequence, int speed, boolean reverse);
    void Tone(int note, int duration);

    void StartSequenceBackGround(int size, int * noteDurationSequence);
    void BackGroundUpdate();
    void StartBackgroundNote();
};
