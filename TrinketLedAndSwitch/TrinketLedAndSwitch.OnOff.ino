/*
    based on video Tutorial 02 for Arduino: Buttons, PWM, and Functions
    https://www.youtube.com/watch?v=_LCCGFSMOr4

    http://arduino.cc/en/Reference/HomePage

    Torres Frederic 2014.12.12
*/

//#define ONOFF 1
#if ONOFF

void LedOn(int pin, boolean state) {

    digitalWrite(pin, state ? HIGH : LOW);
}

const int SWITCH_PIN                  = 0;
const int LED_PIN                     = 1;   // Red LED on the Trinket

boolean _buttonLastStateInLoop = false;
boolean _ledOn                 = false;

boolean IsButtonPressed() {

    return digitalRead(SWITCH_PIN) == HIGH;
}

// If we detect a change of button state between the current loop()
// function execution and the previous one, we wait and re reread 
// the value
boolean GetButtonStateDebounced(boolean lastState) {
    
    boolean state = IsButtonPressed();
    if (state != lastState) {
        delay(5);
        state = IsButtonPressed();
    }
    return state;
}

void setup() {

    pinMode(SWITCH_PIN, INPUT);
    pinMode(LED_PIN,    OUTPUT);
}

void loop() {

    boolean buttonPressed = GetButtonStateDebounced(_buttonLastStateInLoop);

    if (buttonPressed == true && _buttonLastStateInLoop == false) {

        _ledOn = !_ledOn;
    }
    _buttonLastStateInLoop = buttonPressed;
    LedOn(LED_PIN, _ledOn);
}

#endif