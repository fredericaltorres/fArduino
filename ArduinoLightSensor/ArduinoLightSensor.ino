/*************************************************************************

    Using the light sensor CdS photoresistor with an Arduino, as
    a button to trigger command

    https://learn.adafruit.com/photocells/using-a-photocell

    Torres Frederic 2014.12

***************************************************************************/

#include "fArduino.h"

boolean _ledState = false;

// Pins Usage
#define LEFT_PHOTO_RESISTOR_ANALOG_PIN  0
#define RIGHT_PHOTO_RESISTOR_ANALOG_PIN 1

#define ONBOARD_LED_PIN                 13
#define RED_LED_PIN                     11

#define MAX_SENSOR                      2

LightSensorButton  _rightLightSensorButton(RIGHT_PHOTO_RESISTOR_ANALOG_PIN, "LeftLightSensor");
LightSensorButton  _leftLightSensorButton(LEFT_PHOTO_RESISTOR_ANALOG_PIN, "RightLightSensor");
LightSensorButton* _lightSensorButtons[MAX_SENSOR];

void setup() {

    _lightSensorButtons[0] = &_rightLightSensorButton;
    _lightSensorButtons[1] = &_leftLightSensorButton;

    Board.InitializeComputerCommunication(9600, NULL);
    Board.TraceHeader("Photo Resistor as button");
    Board.SetPinMode(ONBOARD_LED_PIN, OUTPUT);
    Board.SetPinMode(RED_LED_PIN, OUTPUT);
}
void loop() {

    for (int s = 0; s < MAX_SENSOR; s++) {

        // Recalibrate the light reference every 15 seconds or on demand
        if (_lightSensorButtons[s]->NeedReference || _lightSensorButtons[s]->ReferenceTimeOut()) {

            _lightSensorButtons[s]->UpdateReferences();
            Board.Trace(Board.Format("Getting reference - %s - Ready.", _lightSensorButtons[s]->ToString().c_str()));
        }
    }

    for (int s = 0; s < MAX_SENSOR; s++) {

        if (_lightSensorButtons[s]->Activated()) {

            _ledState = !_ledState;
            Board.LedOn(ONBOARD_LED_PIN, _ledState);
            Board.LedOn(RED_LED_PIN, _ledState);
            Board.Trace(Board.Format("Changed detected - %s", _lightSensorButtons[s]->ToString().c_str()));
            _lightSensorButtons[s]->NeedReference = true;
        }
    }
}
