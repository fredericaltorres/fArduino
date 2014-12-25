///////////////////////////////////////////////////////////////////////////////
//  
// fArduino.cpp
// Reusable code for Arduino and Trinket programming, mostly to write 
//
// Torres Frederic 2014
//
// MIT License
//
// Remarks the SpeakerManager class require to be compiled for Trinket 8Mhz
//
///////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stdio.h>
#include "fArduino.h"

//#define TRINKET 1 // On the trinket there is no Serial communication

#if defined(TRINKET)
//#define SERIAL_AVAILABLE 0
#else
#define SERIAL_AVAILABLE 1
#endif 

BoardClass::BoardClass() {

    this->_startTime = millis();
#if defined(SERIAL_AVAILABLE)
    this->_serialCommunicationInitialized = false;
#endif
}
BoardClass::~BoardClass() {

}

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;
extern struct __freelist *__flp; /* The head of the free list structure */

/*
* The free list structure as maintained by the
* avr-libc memory allocation routines.
*/
struct __freelist {
    size_t sz;
    struct __freelist *nx;
};

/* Calculates the size of the free list */
int freeListSize() {
    struct __freelist* current;
    int total = 0;
    for (current = __flp; current; current = current->nx) {
        total += 2; /* Add two bytes for the memory block's header  */
        total += (int)current->sz;
    }
    return total;
}

int BoardClass::GetFreeMemory() {

    int free_memory;
    if ((int)__brkval == 0) {
        free_memory = ((int)&free_memory) - ((int)&__heap_start);
    }
    else {
        free_memory = ((int)&free_memory) - ((int)__brkval);
        free_memory += freeListSize();
    }
    return free_memory;
}

String BoardClass::Format(char *format, ...) {

    String formated = String("");
    char tmpBuf[16]; // temp buffer to format number
    va_list argptr;
    va_start(argptr, format);

    while (*format != '\0') {

        if (*format == '%') {
            format++;
            if (*format == '%') { // string
                formated.concat("%");
            }
            else if (*format == 's') { // string
                char* s = va_arg(argptr, char *);
                formated.concat(String(s));
            }
            else if (*format == 'c') { // character
                char c = (char)va_arg(argptr, int);
                formated.concat(String(c));
            }
            else if (*format == 'd') { // integer
                int d = va_arg(argptr, int);
                formated.concat(String(d));
            }
            else if (*format == 'u') { // un signed integer
                unsigned int ui = va_arg(argptr, unsigned int);
                formated.concat(String(ui));
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

#if !defined(TRINKET)
                // Cannot be compiled on the Trinket. Will fix it later
                double d = va_arg(argptr, double);
                formated.concat(String(d));
#endif
            }
            else if (*format == 'b') { // boolean not standard

                //bool d = va_arg(argptr, bool);
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
            formated.concat(String(c));
        }
        format++;
    }
    va_end(argptr);
    return formated;
}

char * BoardClass::GetTime() {

    static char buffer[MAX_FORMAT_SIZE];

    unsigned long secSinceStart = (millis() - this->_startTime) / 1000;

    int hours       = secSinceStart / 3600;
    secSinceStart  -= hours * 3600;
    int minutes     = secSinceStart / 60;
    secSinceStart  -= minutes * 60;
    int seconds     = secSinceStart;

    snprintf(buffer, MAX_FORMAT_SIZE, "%02d:%02d:%02d", hours, minutes, seconds);
    return buffer;
}

void BoardClass::ClearKeyboard() {

#if defined(SERIAL_AVAILABLE)
    while (Serial.available())
        Serial.read();
#endif
}

void BoardClass::Trace(String msg) {

    this->Trace(msg.c_str());
}
// http://arduino.stackexchange.com/questions/176/how-do-i-print-multiple-variables-in-a-string
void BoardClass::Trace(const char * msg) {

    Trace((char*)msg);
}
void BoardClass::Trace(char * msg) {

    #if defined(SERIAL_AVAILABLE)
    if (this->_serialCommunicationInitialized) {
        Serial.println(msg);
        Serial.flush();
    }
    #endif
}

char * PadRight(char * s, char * padding, int max) {

    while (strlen(s) < max) {
        s = strcat(s, padding);
    }
    return s;
}

void BoardClass::TraceHeader(char * msg) {

    int maxPad = 64;

    char barString[MAX_FORMAT_SIZE];
    memset(barString, 0, MAX_FORMAT_SIZE);
    PadRight(barString, TRACE_HEADER_CHAR, maxPad);

    char msg2[MAX_FORMAT_SIZE];
    memset(msg2, 0, MAX_FORMAT_SIZE);
    strcpy(msg2, TRACE_HEADER_CHAR);
    strcat(msg2, " ");
    strcat(msg2, msg);
    PadRight(msg2, " ", maxPad - 1);
    PadRight(msg2, TRACE_HEADER_CHAR, maxPad);

    this->Trace(barString);
    this->Delay(100);
    this->Trace(msg2);
    this->Delay(100);
    this->Trace(barString);
}

void BoardClass::TraceFormat(char * format, char *s) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, s);
    this->Trace(buffer);
}

void BoardClass::TraceFormat(char * format, char *s1, char *s2) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, s1, s2);
    this->Trace(buffer);
}

void BoardClass::TraceFormat(char * format, char *s1, char *s2, char * s3) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, s1, s2, s3);
    this->Trace(buffer);
}

void BoardClass::TraceFormat(char * format, char d1) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, d1);
    this->Trace(buffer);
}

void BoardClass::TraceFormat(char * format, int d1) {

#if defined(SERIAL_AVAILABLE)
    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, d1);
    this->Trace(buffer);
#endif
}

void BoardClass::TraceFormat(char * format, int d1, int d2) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, d1, d2);
    this->Trace(buffer);
}

/// snprintf fr float does not work for the Arduino
void BoardClass::TraceFormat(char * format, float f1) {

    char buffer[MAX_FORMAT_SIZE];
    String f1s = dtostrf((double)f1, 2, 2, buffer);
    snprintf(buffer, MAX_FORMAT_SIZE, format, f1s.c_str());
    this->Trace(buffer);
}

void BoardClass::TraceFormat(char * format, double f1, double f2) {

    char buffer[MAX_FORMAT_SIZE];
    char bufferFloat1[MAX_FORMAT_SIZE];
    char bufferFloat2[MAX_FORMAT_SIZE];

    String f1s = dtostrf((double)f1, 2, 2, bufferFloat1);
    String f2s = dtostrf((double)f2, 2, 2, bufferFloat2);

    snprintf(buffer, MAX_FORMAT_SIZE, format, f1s.c_str(), f2s.c_str());
    this->Trace(buffer);
}


/// snprintf fr float does not work for the Arduino
//char * BoardClass::ToString(double d) {
//
//    char buffer[MAX_FORMAT_SIZE];
//    String f1s = dtostrf(d, 2, 2, buffer);
//    return (char*)f1s.c_str();
//}
//char * BoardClass::ToString(float f) {
//
//    return this->ToString((double)f);
//}

void BoardClass::InitializeComputerCommunication(unsigned long speed, char * message) {

#if defined(SERIAL_AVAILABLE)
    Serial.begin(speed);
    this->_serialCommunicationInitialized = true;
    if (message) {
        this->Trace(message);
    }
#endif
}
void BoardClass::LedOn(int pin, boolean state, int delay) {

    this->LedOn(pin, state);
    this->Delay(delay);
}
void BoardClass::LedOn(int pin, boolean state) {

    digitalWrite(pin, state ? HIGH : LOW);
}
void BoardClass::LedSet(int pin, int level) {

    analogWrite(pin, level);
}
void BoardClass::SetPinMode(uint8_t pin, uint8_t type) {

    pinMode(pin, type);
}
void BoardClass::Delay(unsigned long l) {

    delay(l);
}
///////////////////////////////////////////////////////////////////////////////
// If we detect a change of button state between the current loop()
// function execution and the previous one, we wait and re reread 
// the value
boolean BoardClass::GetButtonStateDebounced(int pin, boolean lastState) {

    boolean state = digitalRead(pin) == HIGH;
    if (state != lastState) {
        delay(5);
        state = digitalRead(pin) == HIGH;
    }
    return state;
}

BoardClass Board;

/////////////////////////////////////////////////////
/// Led
/// Represent the concept of a led, mostly to manage a blinking LED
/// without blocking the controller loop
Led::Led(int pin) {

    this->_pin = pin;
    this->_state = false;
    this->_rate = 0;
}
Led::~Led() {

}
void Led::SetState(boolean on) {

    Board.LedOn(this->_pin, on);
    this->_state = on;
}
void Led::SetLevel(int level) {

    if (level != this->_level) {

        Board.LedSet(this->_pin, level);
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

    if (GetBlinkDurationCycle() > this->_rate)  { // We need to reverse the mode of the led

        this->_state = !this->_state;
        this->SetState(this->_state);
        this->_blinkStartTime = millis();
    }

    /*
    this->_state = !this->_state;
    this->SetState(this->_state);
    this->_blinkStartTime = millis();
    Board.Delay(this->_rate);
    */
}

//////////////////////////////////////////////////////
/// MultiState Button
///
MultiStateButton::MultiStateButton(int pin, Led * led, int maxState, const int * ledIntensityArray) {

    this->_pin = pin;
    this->_previousPin = UNDEFINED_PIN;
    this->_maxState = maxState;
    this->_ledIntensityArray = ledIntensityArray;
    this->LedInstance = led;
    this->StateIndex = 0;
    this->NextButtonLastStateInLoop = false;
    this->PreviousButtonLastStateInLoop = false;
}
MultiStateButton::~MultiStateButton() {

}
void MultiStateButton::SetPreviousButton(int pin) {

    this->_previousPin = pin;
}
// Return true if the user switch to state state and we never queried it before
boolean MultiStateButton::StateChangeFor(int state) {

    if (this->StateIndex == state) {

        boolean r = this->_statedChanged;
        if (r) {
            this->_statedChanged = false;
        }
        return r;
    }
    else return false;
}
void MultiStateButton::NextState() {

    this->StateIndex++;
    if (this->StateIndex >= this->_maxState)
        this->StateIndex = 0;
    this->_statedChanged = true;
}
void MultiStateButton::PreviousState() {

    this->StateIndex--;
    if (this->StateIndex < 0)
        this->StateIndex = this->_maxState - 1;
    this->_statedChanged = true;
}
boolean MultiStateButton::GetButtonStateDebounced() {

    boolean state = digitalRead(this->_pin) == HIGH;

    if (state != this->NextButtonLastStateInLoop) {

        delay(5);
        state = digitalRead(this->_pin) == HIGH;
    }
    return state;
}
boolean MultiStateButton::GetPreviousButtonStateDebounced() {

    if (this->_previousPin != UNDEFINED_PIN) {

        boolean state = digitalRead(this->_previousPin) == HIGH;

        if (state != this->PreviousButtonLastStateInLoop) {

            delay(5);
            state = digitalRead(this->_previousPin) == HIGH;
        }
        return state;
    }
    else return false;
}
void MultiStateButton::UpdateUI() {

    if (this->LedInstance->IsBlinking()) {

        this->LedInstance->Blink();
    }
    else{
        this->LedInstance->SetLevel(this->_ledIntensityArray[this->StateIndex]);
    }
}



//////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////
///  Temperature Manager
///
TemperatureManager::TemperatureManager() {

}
TemperatureManager::~TemperatureManager() {

}
float TemperatureManager::CelsiusToFahrenheit(float celsius) {

    return (9.0 / 5.0 * celsius) + 32.0;
}
void TemperatureManager::Add(float celsius) {

}



//////////////////////////////////////////////////////
///  SpeakerManager
/// based on http://www.instructables.com/id/Arduino-Basics-Making-Sound/step2/Playing-A-Melody/
///

SpeakerManager::SpeakerManager(byte pin) {

    this->_pin = pin;
    this->BackGroundOn = false;
}
SpeakerManager::~SpeakerManager() {

}
void SpeakerManager::PlaySequence(int size, int * noteDurationSequence) {

    this->PlaySequence(size, noteDurationSequence, SPEAKERMANAGER_PLAY_SEQUENCE_NORMAL, false);
}
void SpeakerManager::PlaySequence(int size, int * noteDurationSequence, int speed) {

    this->PlaySequence(size, noteDurationSequence, speed, false);
}

void SpeakerManager::StartSequenceBackGround(int size, int * noteDurationSequence) {

    this->_backGroundNoteDurationSequence = noteDurationSequence;
    this->_backGroundNoteDurationSequenceSize = size;
    this->_backGroundNoteDurationIndex = 0;
    this->BackGroundOn = true;

    this->StartBackgroundNote();
}

void SpeakerManager::StartBackgroundNote() {

    this->Play(this->_backGroundNoteDurationSequence[this->_backGroundNoteDurationIndex], this->_backGroundNoteDurationSequence[this->_backGroundNoteDurationIndex + 1], SPEAKERMANAGER_PLAY_SEQUENCE_NORMAL);
}

void SpeakerManager::BackGroundUpdate() {

    if (this->BackGroundOn) {

        this->_backGroundNoteDurationIndex += 2;
        if (this->_backGroundNoteDurationIndex >= this->_backGroundNoteDurationSequenceSize) {
            this->BackGroundOn = false;
            return;
        }
        else this->StartBackgroundNote();
    }
}

void SpeakerManager::PlaySequence(int size, int * noteDurationSequence, int speed, boolean reverse) {

    if (reverse) {

        for (int i = size - 1; i >= 0; i -= 2) {

            this->Play(noteDurationSequence[i - 1], noteDurationSequence[i], speed);
        }
    }
    else {
        for (int i = 0; i < size; i += 2) {

            this->Play(noteDurationSequence[i], noteDurationSequence[i + 1], speed);
        }
    }
}
void SpeakerManager::Play(int note, int duration) {

    this->Play(note, duration, SPEAKERMANAGER_PLAY_SEQUENCE_NORMAL);
}
void SpeakerManager::Play(int note, int duration, int speed) {

    this->Play(note, duration, speed, true);
}
void SpeakerManager::Play(int note, int duration, int speed, boolean stop) {

    // to calculate the note duration, take one second divided by the note type. e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    float speedAdjustment = 1.0;
#if defined(TRINKET)
    speedAdjustment = 1.8;
#endif

    int noteDuration = 1000 / ((duration / speed) * speedAdjustment);
    this->Tone(note, noteDuration);

    // To distinguish the notes, set a minimum time between them. 
    // the note's duration + 30% seems to work well:
#if defined(TRINKET)
    delay(noteDuration * 1.30);
#else
    delay(noteDuration * 1.30);
#endif

    if (stop)
        this->Off();
}
void SpeakerManager::Off() {
#if defined(TRINKET)
#else
    noTone(this->_pin);
#endif
}

// the sound producing function <6>
void Trinket_Tone(unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) {

    long delayAmount = (long)(1000000 / frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));

    for (int x = 0; x<loopTime; x++) {

        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(delayAmount);
    }
}

void SpeakerManager::Tone(int note, int duration) {
#if defined(TRINKET)
    Trinket_Tone(this->_pin, note, duration);
#else
    tone(this->_pin, note, duration);
#endif
}

