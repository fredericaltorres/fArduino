#include <fArduino.h>
///////////////////////////////////////////////////////////////////////////////
//  
// fArduino.cpp
// Reusable code for Arduino and Trinket programming, mostly to write clean and
// maintainable class. The fArduino library is only one cpp file with multiples
// classes, but remember that the linker will only use the methods and classes
// used.
//
// Torres Frederic 2014
//
// MIT License
//
// Remarks 
//
// - the SpeakerManager class whem compiled for a Trinket need to be compiled at 8Mhz
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// EEPROMEx.cpp - Extended EEPROM library
// Copyright(c) 2012 Thijs Elenbaas.All right reserved.
// http://michael.bouvy.net/blog/en/2013/06/17/eeprom-advanced-usage-arduino-uno-atmega328-int-char-string/
//
///////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stdio.h>
#include <fArduino.h>

BoardClass::BoardClass() {

    this->_startTime = millis();
    this->_serialCommunicationInitialized = false;
}
BoardClass::~BoardClass() {

}

extern unsigned int       __bss_end;
extern unsigned int       __heap_start;
extern void *             __brkval;
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

bool BoardClass::InBetween(int newValue, int refValue, int plusOrMinuspercent)
{
    int p = refValue*plusOrMinuspercent / 100;
    return (newValue >= refValue - p) && (newValue <= refValue + p);
}

bool BoardClass::InBetween(double newValue, double refValue, double plusOrMinuspercent)
{
    double p = refValue*plusOrMinuspercent / 100.0;
    return (newValue >= refValue - p) && (newValue <= refValue + p);
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

    int hours = secSinceStart / 3600;
    secSinceStart -= hours * 3600;
    int minutes = secSinceStart / 60;
    secSinceStart -= minutes * 60;
    int seconds = secSinceStart;

    snprintf(buffer, MAX_FORMAT_SIZE, "%02d:%02d:%02d", hours, minutes, seconds);
    return buffer;
}
void BoardClass::ClearKeyboard() {

    #if defined(SERIAL_AVAILABLE)
    while (Serial.available())
        Serial.read();
    #endif
}
//
// http://www.baldengineer.com/when-do-you-use-the-arduinos-to-use-serial-flush.html
//
void BoardClass::Trace(char * msg) {

    #if defined(SERIAL_AVAILABLE)
    if (this->_serialCommunicationInitialized) {

        Serial.print("[");
        Serial.print(this->GetTime());
        Serial.print("]");
        Serial.println(msg);
        Serial.flush();
    }
    #endif
}
void BoardClass::TraceNoNewLine(char * msg) {

    #if defined(SERIAL_AVAILABLE)
    if (this->_serialCommunicationInitialized) {

        Serial.print(msg);
        Serial.flush();
    }
    #endif
}
void BoardClass::TraceNoNewLine(const char * msg) {

    this->TraceNoNewLine((char *)msg);
}

void BoardClass::Trace(String msg) {

    this->Trace(msg.c_str());
}
void BoardClass::Trace(const char * msg) {

    Trace((char*)msg);
}
void BoardClass::TraceNoNewLine(const String & msg) {

    this->TraceNoNewLine(msg.c_str());
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
    this->Delay(10);
    this->Trace(msg2);
    this->Delay(10);
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

// Global Signleton
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

/**************************************************
SpeakerManager

based on http://www.instructables.com/id/Arduino-Basics-Making-Sound/step2/Playing-A-Melody/
http://makezine.com/projects/make-35/advanced-arduino-sound-synthesis/

Remark from Jeremy Blum about using the default Arduino tone() method
http://www.jeremyblum.com/2010/09/05/driving-5-speakers-simultaneously-with-an-arduino
The built-in tone() function allows you to generate a squarewave with 50% duty cycle of your
selected frequency on any pin on the arduino.
It relies on one of the arduino?s 3 timers to work in the background.

SPECIFICALLY, IT USES TIMER2, WHICH IS ALSO RESPONSIBLE FOR
CONTROLLING PWM ON PINS 3 AND 11.
SO YOU NATURALLY LOOSE THAT ABILITY WHEN USING THE TONE() FUNCTION.

*/
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
boolean SpeakerManager::BackGroundUpdate() {

    if (this->BackGroundOn) {

        this->_backGroundNoteDurationIndex += 2;

        if (this->_backGroundNoteDurationIndex >= this->_backGroundNoteDurationSequenceSize) {

            this->BackGroundOn = false;
        }
        else this->StartBackgroundNote();
    }
    return this->BackGroundOn;
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
    delay(noteDuration * 1.30);

    if (stop)
        this->Off();
}
void SpeakerManager::Off() {

#if defined(TRINKET)
#else
    noTone(this->_pin);
#endif
}
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

/**************************************************
LightSensorButton

- When used with a 1k resistor, simply passing the hand over the button
will trigger the event.
- When used with a 10k resistor, the user will have to put the finger on
the light sensor
- Possiblity to implement : Put the finger on the button (FingerDown),
wait 3 seconds, remove finger

https://learn.adafruit.com/photocells/using-a-photocell
*/
boolean LightSensorButton::Activated() {

    static byte changeDetectedCounter;

    if (this->ChangeDetected()) {

        #if defined(LIGHTSENSORBUTTON_DEBUG)
        Board.Trace(Board.Format("LightSensorButton(%d) Change detected %d", _pin, changeDetectedCounter));
        #endif

        changeDetectedCounter++;
        if (changeDetectedCounter > 2) {
            Board.Delay(200);
        }
        if (changeDetectedCounter > 5) {
            // Most likely the light has changed quickly in the room and it is not cause by a human
            // passing the had in front of the light sensor.
            // We better give up and request new light reference
            Board.Trace(Board.Format("LightSensorButton(%d) Permanent light change detected", _pin));
            changeDetectedCounter = 0;
            this->NeedReference   = true;
            return false;
        }

        Board.Delay(this->DETECTION_BACK_WAIT_TIME);

        if (this->BackToReferenceValue()) {

            #if defined(LIGHTSENSORBUTTON_DEBUG)
            Board.Trace("Returned to ref value -- Activated");
            #endif
            changeDetectedCounter = 0;
            return true;
        }
    }
}
boolean LightSensorButton::BackToReferenceValue() {
    
    return Board.InBetween(analogRead(this->_pin), this->_referenceValue, this->DETECTION_PERCENT_BACK);
}
boolean LightSensorButton::ChangeDetected() {

    _lastValue           = analogRead(this->_pin);
    _lastDifference      = _referenceValue - _lastValue;
    int expectedChange   = _referenceValue * DETECTION_PERCENT / 100;
    _lastChangeInPercent = ((1.0 * _lastValue / _referenceValue) - 1) * 100.0;
    boolean r            = abs(_lastDifference) >= expectedChange;
    return r;
}
int LightSensorButton::UpdateReferences() {

    int ref = 0;

    for (int i = 0; i < MAX_REFERENCES; i++) {

        ref += analogRead(this->_pin);
        delay(REFERENCE_ACQUISITION_TIME);
    }
    _referenceValue          = ref / MAX_REFERENCES;
    this->NeedReference      = false;
    this->_lastReferenceTime = millis();
    this->ChangeDetected();
    return _referenceValue;
}
boolean LightSensorButton::ReferenceTimeOut() {

    return (millis() - this->_lastReferenceTime) > this->UPDATE_REFERENCE_EVERY_X_SECONDS * 1000;
}
LightSensorButton::LightSensorButton(byte pin, char * name) {

    this->Name                             = name;
    this->UPDATE_REFERENCE_EVERY_X_SECONDS = 15; // Update light reference every 15 seconds
    this->MAX_REFERENCES                   = 3;  // Capture the average of 3 light value to compute the lght reference
    this->REFERENCE_ACQUISITION_TIME       = 250; 
    this->DETECTION_PERCENT                = 24; // If the light change more than +-24% we detected a possible change
    this->DETECTION_PERCENT_BACK           = 8;  // if the light go back +-ReferenceValue, the button was activated by a human (Hopefully, not 100% guaranteed)
    this->DETECTION_BACK_WAIT_TIME         = 250;// Wait time before we check if the light value went back to the reference value

    this->_pin                             = pin;
    this->NeedReference                    = true;
    this->_lastReferenceTime               = 0;
    this->_lastDifference                  = 0;
    this->_lastChangeInPercent             = 0;
    this->_referenceValue                  = 0;
}
LightSensorButton::~LightSensorButton() {

}
boolean LightSensorButton::FingerUp() {

    return this->_lastDifference < 0;
}
boolean LightSensorButton::FingerDown() {

    return this->_lastDifference > 0;
}
String LightSensorButton::ToString() {
    
    return Board.Format("LightSensorButton(%s:%d) { value:%d, diff:%d, diffPercent:%f%% }",
        this->Name.c_str(),
        this->_pin,
        this->_lastValue,
        this->_lastDifference,
        this->_lastChangeInPercent
        );
}


/*
EEPROMEx.cpp - Extended EEPROM library
Copyright (c) 2012 Thijs Elenbaas.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/******************************************************************************
* Includes
******************************************************************************/
//#include "EEPROMex.h"

/******************************************************************************
* Definitions
******************************************************************************/

#define _EEPROMEX_VERSION 1 // software version of this library
#define _EEPROMEX_DEBUG     // Enables logging of maximum of writes and out-of-memory
/******************************************************************************
* Constructors
******************************************************************************/

// Boards with ATmega328, Duemilanove, Uno, Uno SMD, Lilypad - 1024 bytes (1 kilobyte)
// Boards with ATmega1280 or 2560, Arduino Mega series – 4096 bytes (4 kilobytes)
// Boards with ATmega168, Lilypad, old Nano, Diecimila  – 512 bytes
// By default we choose conservative settings
EEPROMClassEx::EEPROMClassEx()
    : _allowedWrites(100)
{
}

/******************************************************************************
* User API
******************************************************************************/

void EEPROMClassEx::setMemPool(int base, int memSize) {
    //Base can only be adjusted if no addresses have already been issued
    if (_nextAvailableaddress == _base)
        _base = base;
    _nextAvailableaddress = _base;

    //Ceiling can only be adjusted if not below issued addresses
    if (memSize >= _nextAvailableaddress)
        _memSize = memSize;

#ifdef _EEPROMEX_DEBUG    
    if (_nextAvailableaddress != _base)
        Serial.println("Cannot change base, addresses have been issued");

    if (memSize < _nextAvailableaddress)
        Serial.println("Cannot change ceiling, below issued addresses");
#endif	

}

void EEPROMClassEx::setMaxAllowedWrites(int allowedWrites) {
#ifdef _EEPROMEX_DEBUG
    _allowedWrites = allowedWrites;
#endif			
}

int EEPROMClassEx::getAddress(int noOfBytes){
    int availableaddress = _nextAvailableaddress;
    _nextAvailableaddress += noOfBytes;

#ifdef _EEPROMEX_DEBUG    
    if (_nextAvailableaddress > _memSize) {
        Serial.println("Attempt to write outside of EEPROM memory");
        return -availableaddress;
    }
    else {
        return availableaddress;
    }
#endif
    return availableaddress;
}


bool EEPROMClassEx::isReady() {
    return eeprom_is_ready();
}

uint8_t EEPROMClassEx::read(int address)
{
    return readByte(address);
}

bool EEPROMClassEx::readBit(int address, byte bit) {
    if (bit> 7) return false;
    if (!isReadOk(address + sizeof(uint8_t))) return false;
    byte byteVal = eeprom_read_byte((unsigned char *)address);
    byte bytePos = (1 << bit);
    return (byteVal & bytePos);
}

uint8_t EEPROMClassEx::readByte(int address)
{
    if (!isReadOk(address + sizeof(uint8_t))) return 0;
    return eeprom_read_byte((unsigned char *)address);
}

uint16_t EEPROMClassEx::readInt(int address)
{
    ABOUT_TO_CALL_EEPROM_API;

    if (!isReadOk(address + sizeof(uint16_t))) return 0;

    uint16_t v = eeprom_read_word((uint16_t *)address);

    DONE_CALLING_EEPROM_API;

    return v;
}

uint32_t EEPROMClassEx::readLong(int address)
{
    if (!isReadOk(address + sizeof(uint32_t))) return 0;
    return eeprom_read_dword((unsigned long *)address);
}

float EEPROMClassEx::readFloat(int address)
{
    if (!isReadOk(address + sizeof(float))) return 0;
    float _value;
    readBlock<float>(address, _value);
    return _value;
}

double EEPROMClassEx::readDouble(int address)
{
    if (!isReadOk(address + sizeof(double))) return 0;
    double _value;
    readBlock<double>(address, _value);
    return _value;
}

bool EEPROMClassEx::write(int address, uint8_t value)
{
    return writeByte(address, value);
}

bool EEPROMClassEx::writeBit(int address, uint8_t bit, bool value) {
    updateBit(address, bit, value);
    return true;
}


bool EEPROMClassEx::writeByte(int address, uint8_t value)
{
    if (!isWriteOk(address + sizeof(uint8_t))) return false;
    eeprom_write_byte((unsigned char *)address, value);
    return true;
}

bool EEPROMClassEx::writeInt(int address, uint16_t value)
{
    ABOUT_TO_CALL_EEPROM_API;

    if (!isWriteOk(address + sizeof(uint16_t))) return false;
    eeprom_write_word((uint16_t *)address, value);

    DONE_CALLING_EEPROM_API;
    return true;
}

bool EEPROMClassEx::writeLong(int address, uint32_t value)
{
    if (!isWriteOk(address + sizeof(uint32_t))) return false;
    eeprom_write_dword((unsigned long *)address, value);
    return true;
}

bool EEPROMClassEx::writeFloat(int address, float value)
{
    return (writeBlock<float>(address, value) != 0);
}

bool EEPROMClassEx::writeDouble(int address, double value)
{
    return (writeBlock<float>(address, value) != 0);
}

bool EEPROMClassEx::update(int address, uint8_t value)
{
    return (updateByte(address, value));
}

bool EEPROMClassEx::updateBit(int address, uint8_t bit, bool value)
{
    if (bit> 7) return false;

    byte byteValInput = readByte(address);
    byte byteValOutput = byteValInput;
    // Set bit
    if (value) {
        byteValOutput |= (1 << bit);  //Set bit to 1
    }
    else {
        byteValOutput &= ~(1 << bit); //Set bit to 0
    }
    // Store if different from input
    if (byteValOutput != byteValInput) {
        writeByte(address, byteValOutput);
    }
    return true;
}

bool EEPROMClassEx::updateByte(int address, uint8_t value)
{
    return (updateBlock<uint8_t>(address, value) != 0);
}

bool EEPROMClassEx::updateInt(int address, uint16_t value)
{
    return (updateBlock<uint16_t>(address, value) != 0);
}

bool EEPROMClassEx::updateLong(int address, uint32_t value)
{
    return (updateBlock<uint32_t>(address, value) != 0);
}

bool EEPROMClassEx::updateFloat(int address, float value)
{
    return (updateBlock<float>(address, value) != 0);
}

bool EEPROMClassEx::updateDouble(int address, double value)
{
    return (writeBlock<double>(address, value) != 0);
}

bool EEPROMClassEx::isWriteOk(int address)
{
#ifdef _EEPROMEX_DEBUG    
    _writeCounts++;
    if (_allowedWrites == 0 || _writeCounts > _allowedWrites) {
        Serial.println("Exceeded maximum number of writes");
        return false;
    }

    if (address > _memSize) {
        Serial.println("Attempt to write outside of EEPROM memory");
        return false;
    }
    else {
        return true;
    }
#endif		
    return true;
}

bool EEPROMClassEx::isReadOk(int address)
{
#ifdef _EEPROMEX_DEBUG    
    if (address > _memSize) {
        Serial.println("Attempt to write outside of EEPROM memory");
        return false;
    }
    else {
        return true;
    }
#endif
    return true;
}

int EEPROMClassEx::_base = 0;
int EEPROMClassEx::_memSize = 512;
int EEPROMClassEx::_nextAvailableaddress = 0;
int EEPROMClassEx::_writeCounts = 0;

EEPROMClassEx EEPROM;

