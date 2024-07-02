//
//
//

#include <stdarg.h>
#include <stdio.h>
#include "fESP32.h"

char __fArduino_InternalCharBuffer[__fArduino_InternalCharBufferSize];

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// http://linux.dd.com.au/wiki/Arduino_Static_Strings

String StringFormatClass::MakeString(char* padding, int max) {

    String r("");
    while (r.length() < max) {
        r.concat(padding);
    }
    return r;
}
String StringFormatClass::PadRight(String source, char* padding, int max) {

    String r(source);
    while (r.length() < max) {
        r.concat(padding);
    }
    return r;
}
String StringFormatClass::PadLeft(String source, char* padding, int max) {

    int neededPadding = max - source.length();
    if (neededPadding <= 0) {
        return source;
    }
    else {
        String r = this->MakeString(padding, neededPadding);
        r.concat(source);
        return r;
    }
}

const char GetTime_FORMAT[]        PROGMEM = { "%02d:%02d:%2d" };

String StringFormatClass::GetTime() {

    unsigned long secSinceStart = millis() / 1000;
    int hours = secSinceStart / 3600;
    secSinceStart -= hours * 3600;
    int minutes = secSinceStart / 60;
    secSinceStart -= minutes * 60;
    int seconds = secSinceStart;
    //String formated             = this->Format(_PM_(GetTime_FORMAT), hours, minutes, seconds);
    String formated = this->Format("%02d:%02d:%2d", hours, minutes, seconds);
    return formated;
}
boolean StringFormatClass::IsDigit(char* format) {

    return (*format >= '0' && *format <= '9');
}

char* StringFormatClass::ProgMem(char* progMemString) {

    return this->GetProgMemString(progMemString);
}
char* StringFormatClass::GetProgMemString(char* progMemString) {

    strcpy_P(__fArduino_InternalCharBuffer, (char*)progMemString);
    return __fArduino_InternalCharBuffer;
}

// http://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
String StringFormatClass::Format(char* format, ...) {

    String formated = String("");
    char tmpBuf[16]; // temp buffer to format number
    va_list argptr;
    va_start(argptr, format);

    int formatSize = 0;

    while (*format != '\0') {

        if (*format == '%') {

            formatSize = 0;
            format++;

            // Check and reading format size if defined
            while (StringFormat.IsDigit(format)) {
                formatSize = *format - '0';
                format++;
            }

            if (*format == '%') { // string
                formated.concat("%");
            }
            else if (*format == 's') { // string
                char* s = va_arg(argptr, char*);
                formated.concat(String(s));
            }
            else if (*format == 'c') { // character
                char c = (char)va_arg(argptr, int);
                formated.concat(String(c));
            }
            else if (*format == 'd') { // decimal/integer
                int d = va_arg(argptr, int);
                formated.concat(StringFormat.PadLeft(String(d), "0", formatSize));
            }
            else if (*format == 'l') { // long
                long d = va_arg(argptr, long);
                formated.concat(String(d));
            }
            else if (*format == 'u') { // un signed integer or long - Not standard, format is %ui or %ul
                format++;
                if (*format == 'i') { // un signed integer
                    unsigned int ui = va_arg(argptr, unsigned int);
                    formated.concat(String(ui));
                }
                if (*format == 'l') { // un signed integer
                    unsigned long ui = va_arg(argptr, unsigned long);
                    formated.concat(String(ui));
                }
            }
            else if (*format == 'x') { // un signed integer hexa

                unsigned int ui = va_arg(argptr, unsigned int);
                snprintf(tmpBuf, sizeof(tmpBuf), "%x", ui);
                formated.concat(String(tmpBuf));
            }
            else if (*format == 'X') { // un signed integer hexa uppercase
                unsigned int ui = va_arg(argptr, unsigned int);
                snprintf(tmpBuf, sizeof(tmpBuf), "%X", ui);
                formated.concat(String(tmpBuf));
            }
            else if (*format == 'f') { // float

                double d = va_arg(argptr, double);
#if defined(ARDUINO_UNO)
                formated.concat(String(d));
#endif
#if defined(TRINKET) || defined(TRINKET_PRO)
                //dtostrf(d, 10, 2)
                sprintf(tmpBuf, "%f", d);
                formated.concat(tmpBuf);
#endif
            }
            else if (*format == 'b') { // boolean not standard

                // bool d = va_arg(argptr, bool);
                int d = va_arg(argptr, int);
                if (d)
                    strcpy(tmpBuf, "true");
                else
                    strcpy(tmpBuf, "false");
                formated.concat(String(tmpBuf));
            }
        }
        else {
            char c = format[0];
            formated.concat(String(format[0]));
        }
        format++;
    }
    va_end(argptr);
    return formated;
}
StringFormatClass StringFormat;

/////////////////////////////////////////////////////
/// Led
/// Represent the concept of a led, mostly to manage a blinking LED
/// without blocking the controller loop
Led::Led(int pin) {

    this->_pin = pin;
    this->_state = false;
    this->_rate = 0;
    pinMode(this->_pin, OUTPUT);
}
Led::~Led() {

}
void Led::SetState(boolean on) {

    digitalWrite(this->_pin, on ? HIGH : LOW);
    this->_state = on;
}
void Led::SetLevel(int level) {

    if (level != this->_level) {

        analogWrite(this->_pin, level);
        this->_state = level > 0;
        this->_level = level;
    }
}
void Led::SetBlinkMode(unsigned long rate) {

    this->_rate = rate;
    this->_blinkStartTime = millis();
    this->_state = true;
    this->SetState(this->_state);
}
unsigned long Led::GetBlinkDurationCycle() {

    return millis() - this->_blinkStartTime;
}
void Led::SetBlinkModeOff() {

    this->_rate = 0;
    this->_state = false;
    this->SetLevel(0);
}
boolean Led::IsBlinking() {

    return this->_rate != 0;
}
void Led::Blink() {

    if (GetBlinkDurationCycle() > this->_rate) { // We need to reverse the mode of the led

        this->_state = !this->_state;
        this->SetState(this->_state);
        this->_blinkStartTime = millis();
    }
}
void Led::Blink(int blinkCount, int waitTime) {

    for (int z = 0; z < blinkCount; z++) {

        this->SetState(true);
        delay(waitTime);
        this->SetState(false);
        delay(waitTime);
    }
    this->SetState(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// TimeOut
///
TimeOut::TimeOut(unsigned long duration) {

    this->Counter = -1;
    this->_duration = duration;
    this->Reset();
}
TimeOut::~TimeOut() {
}
boolean TimeOut::IsTimeOut() {

    boolean b = (millis() - this->_time) > this->_duration;
    if (b) {
        this->Reset();
    }
    return b;
}
boolean TimeOut::EveryCalls(unsigned long callCount) {

    return this->Counter % callCount == 0;
}
void TimeOut::Reset() {

    this->_time = millis();
    this->Counter++;
}
String TimeOut::ToString() {

    return StringFormat.Format("TimeOut counter:%l, duration:%l, time:%l", this->Counter, this->_duration, this->_time);
}