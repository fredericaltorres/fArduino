/*************************************************************************

    Using the light sensor CdS photoresistor with an Arduino, as
    a button to trigger command

    Torres Frederic 2014.12

***************************************************************************/

#include "fArduino.h"

boolean _ledState = false;

// Pins Usage
#define PHOTO_RESISTOR_ANALOG_PIN 0
#define ONBOARD_LED_PIN 13

void setup() {

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Photo Resistor as button");
    Board.SetPinMode(ONBOARD_LED_PIN, OUTPUT);
}

const byte UPDATE_REFERENCE_EVERY_X_SECONDS = 10;
const byte MAX_REFERENCES                   = 3;
const byte REFERENCE_ACQUISITION_TIME       = 250;
const byte DETECTION_PERCENT                = 17;
boolean _needReference                      = true;
unsigned long _lastReferenceTime            = 0;
int _referenceValue;


int GetReferences() {

    int ref = 0;

    for (int i = 0; i < MAX_REFERENCES; i++) {

        ref += analogRead(PHOTO_RESISTOR_ANALOG_PIN);
        Board.Delay(REFERENCE_ACQUISITION_TIME);
    }
    _referenceValue = ref / MAX_REFERENCES;
    _needReference  = false;
    return _referenceValue;
}

boolean ChangeDetected(int newValue) {

    int dif            = abs(_referenceValue - newValue);
    int expectedChange = _referenceValue * DETECTION_PERCENT / 100;

    if ((dif >= (expectedChange))) {
        Serial.println(_referenceValue - newValue);
    }

    return (dif >= (expectedChange));
}

void loop() {

    if ((_needReference) || (millis() - _lastReferenceTime > UPDATE_REFERENCE_EVERY_X_SECONDS * 1000)) {

        Board.TraceNoNewLine(Board.Format("[%s]Getting reference, ", Board.GetTime()));
        Board.TraceNoNewLine(Board.Format("Ref value: %d, ", GetReferences()));
        Board.Trace("Ready.");
        _lastReferenceTime = millis();
    }

    int photoResistorValue = analogRead(PHOTO_RESISTOR_ANALOG_PIN);

    if (ChangeDetected(photoResistorValue)) {

        _ledState = !_ledState;
        Board.LedOn(ONBOARD_LED_PIN, _ledState);

        double changeInPercent = (1.0 * photoResistorValue / _referenceValue) - 1;
        Board.Trace(Board.Format("[%s]Change Detected %d, %f%%", Board.GetTime(), photoResistorValue, changeInPercent));
        
        Board.Delay(250);
        _needReference = true;
    }
}
