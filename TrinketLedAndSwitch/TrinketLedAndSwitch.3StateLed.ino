/*
    based on video Tutorial 02 for Arduino: Buttons, PWM, and Functions
    https://www.youtube.com/watch?v=_LCCGFSMOr4

    http://arduino.cc/en/Reference/HomePage

    Torres Frederic 2014.12.12
*/

//#define THREE_STATE 1
#if THREE_STATE
/*
based on video Tutorial 02 for Arduino: Buttons, PWM, and Functions
https://www.youtube.com/watch?v=_LCCGFSMOr4

http://arduino.cc/en/Reference/HomePage

Torres Frederic 2014.12.12
*/

#include "fArduino.h"

BoardClass Board;

const int SWITCH_PIN                  = 0;
const int LED_PIN                     = 1;   // Red LED on the Trinket

//const int LED_LIGTH_STEP_VALUES_LEN   = 3;
const int LED_LIGTH_STEP_VALUES[]     = { 0, 20, 200 };
//const int LED_LIGTH_MAX               = 255;
//const int LED_LIGTH_MIN               = 0;

int     _ledLevelIndex                = 0;
boolean _buttonLastStateInLoop        = false;

void setup() {

    Board.SetPinMode(SWITCH_PIN, INPUT);
    Board.SetPinMode(LED_PIN, OUTPUT);
}

void loop() {

    boolean buttonPressed = Board.GetButtonStateDebounced(SWITCH_PIN, _buttonLastStateInLoop);
    int ledLevel          = LED_LIGTH_STEP_VALUES[_ledLevelIndex];

    if (buttonPressed == true && _buttonLastStateInLoop == false) {

        _ledLevelIndex += 1;
        ledLevel = LED_LIGTH_STEP_VALUES[_ledLevelIndex];
        if (_ledLevelIndex >= ArraySize(LED_LIGTH_STEP_VALUES))
            _ledLevelIndex = 0;
    }
    _buttonLastStateInLoop = buttonPressed;
    Board.LedSet(LED_PIN, ledLevel);
}

#endif