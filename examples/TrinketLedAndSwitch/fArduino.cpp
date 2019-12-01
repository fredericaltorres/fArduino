///////////////////////////////////////////////////////////////////////////////
//  
// fArduino.cpp
// Reusable code for Arduino and Trinket programming, mostly to write 
//
// Torres Frederic 2014
//
// MIT License
///////////////////////////////////////////////////////////////////////////////

#include "fArduino.h"

BoardClass::BoardClass() {

    this->_serialCommunicationInitialized = false;
}
BoardClass::~BoardClass() {

}

void BoardClass::ClearKeyboard() {
    while (Serial.available())
        Serial.read();
}

// http://arduino.stackexchange.com/questions/176/how-do-i-print-multiple-variables-in-a-string
void BoardClass::Trace(char * msg) {

    if (this->_serialCommunicationInitialized) {
        Serial.println(msg);
        Serial.flush();
    }
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
    PadRight(barString, "*", maxPad);

    char msg2[MAX_FORMAT_SIZE];
    memset(msg2, 0, MAX_FORMAT_SIZE);
    strcpy(msg2, "* ");
    strcat(msg2, msg);
    PadRight(msg2, " ", maxPad - 1);
    PadRight(msg2, "*", maxPad);

    this->Trace(barString);
    this->Trace(msg2);
    this->Trace(barString);
}

void BoardClass::TraceFormat(char * format, char *s) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, s);
    this->Trace(buffer);
}

void BoardClass::TraceFormat(char * format, char d1) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, d1);
    this->Trace(buffer);
}

void BoardClass::TraceFormat(char * format, int d1) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, d1);
    this->Trace(buffer);
}


void BoardClass::TraceFormat(char * format, int d1, int d2) {

    char buffer[MAX_FORMAT_SIZE];
    snprintf(buffer, MAX_FORMAT_SIZE, format, d1, d2);
    this->Trace(buffer);
}

void BoardClass::InitializeComputerCommunication(unsigned long speed, char * message) {

    Serial.begin(speed);
    this->_serialCommunicationInitialized = true;
    if (message) {
        this->Trace(message);
    }
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

    this->_pin   = pin;
    this->_state = false;
    this->_rate  = 0;
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

    this->_rate           = rate;
    this->_blinkStartTime = millis();
    this->_state          = true;
    this->SetState(this->_state);
}
unsigned long Led::GetBlinkDurationCycle() {

    return millis() - this->_blinkStartTime;
}
void Led::SetBlinkModeOff() {

    this->_rate  = 0;
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

    this->_pin                          = pin;
    this->_previousPin                  = UNDEFINED_PIN; 
    this->_maxState                     = maxState;
    this->_ledIntensityArray            = ledIntensityArray;
    this->LedInstance                   = led;
    this->StateIndex                    = 0;
    this->NextButtonLastStateInLoop     = false;
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
        this->StateIndex = this->_maxState-1;
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

    this->Counter   = -1;
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
void TimeOut::Reset() {

    this->_time = millis();
    this->Counter++;
}