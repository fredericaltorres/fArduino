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
    protected:
    public:
        BoardClass();
        ~BoardClass();
        boolean GetButtonStateDebounced(int pin, boolean lastState);
        void LedOn(int pin, boolean state);
        void LedOn(int pin, boolean state, int delay);
        void LedSet(int pin, int level);
        void SetPinMode(uint8_t, uint8_t);
        void Delay(unsigned long);

        void InitializeComputerCommunication(unsigned long speed, char * message);
        void Trace(char * msg);
        void TraceHeader(char * msg);
        void TraceFormat(char * format, int d1);
        void TraceFormat(char * format, int d1, int d2);
        void TraceFormat(char * format, char *s);
        void TraceFormat(char * format, char d1);

        void ClearKeyboard();
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
