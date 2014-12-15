/*
    Implement a 5 state button. By clicking on the button the button activate one 
    of the 5 state. A led display the 5 states.
    States
        0 - No ligth
        1 - Dim light
        2 - Bright ligt
        3 - Led flashing quickly
        4 - Led flashing slowly

    based on video Tutorial 02 for Arduino: Buttons, PWM, and Functions
    https://www.youtube.com/watch?v=_LCCGFSMOr4

    http://arduino.cc/en/Reference/HomePage

    Torres Frederic 2014.12.12

    Diagram for one button
        5v => Switch => 10k Resistor => Ground
                                    => Pin 0 Trinket
                    
    Diagram for 2 button2
        5v => Switch1 => 10k Resistor => Ground
                                      => Pin 0 Trinket
              Switch2 => 10k Resistor => Ground
                                      => Pin 1 Trinket
*/

#include "fArduino.h"

const int SWITCH_PIN                  = 0;
const int SWITCH_PIN_PREVIOUS         = 1;
const int LED_PIN                     = 1;  // Red LED on the Trinket
const int LED_LIGTH_STEP_VALUES[]     = { 0, 20, 200, 255, 255 }; // Define the led intensity, 255 we will blink
const int LED_BLINKING_RATES[]        = { 100, 400 }; 

const int   _blinking1LevelIndex      = 3;
const int   _blinking2LevelIndex      = 4;

Led              _onBoardLed(LED_PIN);
MultiStateButton _5StatesButton(SWITCH_PIN, &_onBoardLed, ArraySize(LED_LIGTH_STEP_VALUES), &LED_LIGTH_STEP_VALUES[0]);

void setup() {

    Board.SetPinMode(SWITCH_PIN,            INPUT);
    Board.SetPinMode(SWITCH_PIN_PREVIOUS,   INPUT);
    Board.SetPinMode(LED_PIN,               OUTPUT);

    // _5StatesButton.SetPreviousButton(SWITCH_PIN_PREVIOUS);
}

void CheckToActivateBlinkingMode() {

    if ((_5StatesButton.StateIndex == _blinking1LevelIndex) || (_5StatesButton.StateIndex == _blinking2LevelIndex)) {

        _5StatesButton.LedInstance->SetBlinkMode(LED_BLINKING_RATES[_5StatesButton.StateIndex - 3]);
    }
    else {
        if (_5StatesButton.LedInstance->IsBlinking()) {
            _5StatesButton.LedInstance->SetBlinkModeOff();
        }
    }
}

void loopNextOnly() {

    boolean buttonPressed = _5StatesButton.GetButtonStateDebounced();

    if (buttonPressed == true && _5StatesButton._buttonLastStateInLoop == false) {

        _5StatesButton.NextState();
        CheckToActivateBlinkingMode();
    }
    _5StatesButton._buttonLastStateInLoop = buttonPressed;
    _5StatesButton.UpdateUI();
}

void loopPreviousOnly() {

    boolean previousButtonPressed = _5StatesButton.GetPreviousButtonStateDebounced();

    if (previousButtonPressed == true && _5StatesButton._previousButtonLastStateInLoop == false) {

        _5StatesButton.PreviousState();
        CheckToActivateBlinkingMode();
    }
    _5StatesButton._previousButtonLastStateInLoop = previousButtonPressed;
    _5StatesButton.UpdateUI();
}

/// See blog post about using 2 switch
// http://www.varesano.net/blog/fabio/serial-communication-arduino-and-processing-simple-examples-and-arduino-based-gamepad-int
void loopBoth() {

    boolean buttonPressed         = _5StatesButton.GetButtonStateDebounced();
    boolean previousButtonPressed = false;

    if (buttonPressed == true && _5StatesButton._buttonLastStateInLoop == false) {

        _5StatesButton.NextState();
        CheckToActivateBlinkingMode();
    }
    else {

        previousButtonPressed = _5StatesButton.GetPreviousButtonStateDebounced();
        /*
        if (previousButtonPressed == true && _5StatesButton._previousButtonLastStateInLoop == false) {

            _5StatesButton.PreviousState();
            CheckToActivateBlinkingMode();
        }*/
    }
    _5StatesButton._previousButtonLastStateInLoop = previousButtonPressed;
    _5StatesButton._buttonLastStateInLoop         = buttonPressed;
    _5StatesButton.UpdateUI();
}

void loop() {
    loopNextOnly();
}