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

#define ARDUINO 1

#if BACK_BUTTON
const int SWITCH_PIN_PREVIOUS         = 2; // Only used if add a back button
#endif

#if ARDUINO
const int SWITCH_PIN                  = 3;
const int LED_PIN                     = 13; // Arduino Uno on board led
const int LED_LIGTH_STEP_VALUES[]     = { 0, 128, 255, 255, 255 }; // Define the led intensity, 255 we will blink
#endif

#if TRINKET
const int SWITCH_PIN = 0; // should be 0
const int LED_PIN    = 1; // Red LED on the Trinket
const int INTENSITY01 = 20;
const int LED_LIGTH_STEP_VALUES[] = { 0, 20, 200, 255, 255 }; // Define the led intensity, 255 we will blink
#endif

const int LED_BLINKING_RATES[]        = { 100, 400 };

const int   _blinking1LevelIndex      = 3;
const int   _blinking2LevelIndex      = 4;

Led              _onBoardLed(LED_PIN);  // The led representing the User Interface

MultiStateButton _5StatesButton(SWITCH_PIN, &_onBoardLed, ArraySize(LED_LIGTH_STEP_VALUES), &LED_LIGTH_STEP_VALUES[0]);

#define USER_INPUT_STATE 0

void setup() {
    
    Board.InitializeComputerCommunication(115200, "Initializing...");
    Board.TraceHeader("5 State App");

    Board.SetPinMode(SWITCH_PIN,            INPUT);
    Board.SetPinMode(LED_PIN,               OUTPUT);

    #if BACK_BUTTON
        Board.SetPinMode(SWITCH_PIN_PREVIOUS, INPUT);
        _5StatesButton.SetPreviousButton(SWITCH_PIN_PREVIOUS);
    #endif

    Board.ClearKeyboard();
    Board.Trace("Ready...");
    Board.TraceFormat("State Changed :%d", _5StatesButton.StateIndex);
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

    if (buttonPressed == true && _5StatesButton.NextButtonLastStateInLoop == false) {

        _5StatesButton.NextState();
        CheckToActivateBlinkingMode();
        Board.TraceFormat("State Changed :%d", _5StatesButton.StateIndex);
    }
    _5StatesButton.NextButtonLastStateInLoop = buttonPressed;
    // Update the led associated with the MultiStateButton including managing the
    // blinking without using delay()
    _5StatesButton.UpdateUI();

    if (_5StatesButton.StateChangeFor(USER_INPUT_STATE)) {

        Board.TraceHeader("Menu");
        Board.Trace("1) Function 1");
        Board.Trace("2) Function 2");
        Board.Trace("");
    }

    if (Serial.available() != 0) {

        int c = Serial.read();
        int k = c - '0';

        if (_5StatesButton.StateIndex == USER_INPUT_STATE) {

            switch (c) {
                case '1': Board.Trace("User call function 1"); break;
                case '2': Board.Trace("User call function 2"); break;
                default: Board.TraceFormat("Unknown command:%c", c); break;
            }
        }
        else {
            Board.TraceFormat("The app do not accept user input in state :%d", _5StatesButton.StateIndex);
        }
        Board.ClearKeyboard();
    }
}

void loop() {

    loopNextOnly();
}

#if BACK_BUTTON

/// See blog post about using 2 switch
// http://www.varesano.net/blog/fabio/serial-communication-arduino-and-processing-simple-examples-and-arduino-based-gamepad-int
void loopBoth() {

    boolean buttonPressed = _5StatesButton.GetButtonStateDebounced();
    boolean previousButtonPressed = false;

    if (buttonPressed == true && _5StatesButton.NextButtonLastStateInLoop == false) {

        _5StatesButton.NextState();
        CheckToActivateBlinkingMode();
    }
    else {

        previousButtonPressed = _5StatesButton.GetPreviousButtonStateDebounced();
        if (previousButtonPressed == true && _5StatesButton.PreviousButtonLastStateInLoop == false) {

            _5StatesButton.PreviousState();
            CheckToActivateBlinkingMode();
        }
    }
    _5StatesButton.PreviousButtonLastStateInLoop = previousButtonPressed;
    _5StatesButton.NextButtonLastStateInLoop = buttonPressed;
    _5StatesButton.UpdateUI();
}

#endif