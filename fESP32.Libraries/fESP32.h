// fESP32.h

#ifndef _FESP32_h
#define _FESP32_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define __fArduino_InternalCharBufferSize 128


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// StringFormatClass
/// Create a sigleton object named StringFormat exposing method to format string
/// The formating follow the sprinf syntax http://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
/// with some extended syntax for unsigned int and long and boolean
////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StringFormatClass {
public:
    String Format(char* format, ...);
    String GetTime();
    String PadRight(String source, char* padding, int max);
    String PadLeft(String source, char* padding, int max);
    String MakeString(char* padding, int max);
    boolean IsDigit(char* format);
    char* GetProgMemString(char* progMemString);
    char* ProgMem(char* progMemString);
};
extern StringFormatClass StringFormat;




////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Led
///
class Led {

    private:
        int _pin;
        unsigned long _rate;
        boolean _state;
        int _level;
        unsigned long _blinkStartTime;

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
        void Blink(int blinkCount, int waitTime);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        String ToString();
};


#endif

