/************************************

http://arduino.cc/en/Reference/HomePage
https://learn.adafruit.com/introducing-trinket/pinouts

https://github.com/trinketbook/GettingStartedWithTrinket

Trinket: 
    https://www.adafruit.com/products/1501
    5 GPIO
        2 Shared (3,4)
        2 Pin have PWM need for Speaker

    Getting Started with Adafruit Trinket: 15 Projects with the Low-Cost AVR ..
        https://books.google.com/books?id=SyuiBAAAQBAJ&pg=PT48&lpg=PT48&dq=TRINKET+SPEAKER&source=bl&ots=blIOuuvJU-&sig=F9UypcshplA8lb-sETa5L-4FFig&hl=en&sa=X&ei=RCqWVNS0K4GYgwTU9IPwBQ&ved=0CD0Q6AEwBQ#v=onepage&q=TRINKET%20SPEAKER&f=false


    http://www.instructables.com/id/Controlling-20-Leds-from-5-Arduino-pins-using-Cha/
    http://www.instructables.com/id/How-to-access-5-buttons-through-1-Arduino-input/


    Controlling 8 Led
        http://www.arduino.cc/en/Tutorial/ShiftOut

    Controlling InStyle LED LED Tape Using Arduino Uno
        https://www.youtube.com/watch?v=zJAdzs3BqjE#t=259

Torres Frederic 2014.12.10
*/

#include "fArduino.h"

#define MAX_LED_STATE 4
int ledState = 0; // 0..3

#define RED_LED_ONBAORD_PIN 13
#define SWITCH_PIN      0
#define SPEAKER_PIN     1
//#define RED_LED_1_PIN     3
//#define GREEN_LED_1_PIN   4

boolean _buttonLastStateInLoop = false;

//int musicSequenceIntro[] = {
//    NOTE_C4, 8,
//    NOTE_C4, 8,
//    NOTE_G3, 8,
//    NOTE_G3, 8,
//    NOTE_A3, 4,
//    NOTE_G3, 4,
//    NOTE_SILENCE, 4,
//    NOTE_B3, 4,
//    NOTE_C4, 8,
//    NOTE_C3, 8,
//    NOTE_C2, 8,
//    NOTE_C1, 4,
//};

#define FACTOR 4

int pivolDeNuitSeq01[] = {
    NOTE_E4, 8 * FACTOR,
    NOTE_FS4, 8 * FACTOR,
    NOTE_A4, 8 * FACTOR,
    NOTE_B4, 8 * (FACTOR/2),
};
int pivolDeNuitSeq01Reverse[] = {
    
    NOTE_B4, 8 * FACTOR,
    NOTE_A4, 8 * FACTOR,
    NOTE_FS4, 8 * FACTOR,
    NOTE_E4, 8 * (FACTOR/2),
};

// http://www.unimusica-peru.com/partit21.gif

int WeWishYouAMerryChristmas_Arduino[] = {

    NOTE_G2, 4,
    NOTE_C3, 4,
    NOTE_C3, 8,
    NOTE_D3, 8,
    NOTE_C3, 8,
    NOTE_B2, 8,
    NOTE_A2, 2,

    NOTE_A2, 4,
    NOTE_D3, 4,
    NOTE_D3, 8,
    NOTE_E3, 8,
    NOTE_D3, 8,
    NOTE_C3, 8,
    NOTE_B2, 2,
    NOTE_G2, 4,

    NOTE_E3, 4,
    NOTE_E3, 8,
    NOTE_F3, 8,
    NOTE_E3, 8,
    NOTE_D3, 8,
    NOTE_C3, 4,
    NOTE_A2, 4,
    NOTE_G2, 4,
    NOTE_A2, 4,

    NOTE_D3, 4,
    NOTE_B2, 4,
    NOTE_C3, 2,
};

int WeWishYouAMerryChristmas[] = {
    
    NOTE_G4, 4,
    NOTE_C5, 4,
    NOTE_C5, 8,
    NOTE_D5, 8,
    NOTE_C5, 8,
    NOTE_B4, 8,
    NOTE_A4, 2,
    
    NOTE_A4, 4,
    NOTE_D5, 4,
    NOTE_D5, 8,
    NOTE_E5, 8,
    NOTE_D5, 8,
    NOTE_C5, 8,
    NOTE_B4, 2,
    NOTE_G4, 4,

    NOTE_E5, 4,
    NOTE_E5, 8,
    NOTE_F5, 8,
    NOTE_E5, 8,
    NOTE_D5, 8,
    NOTE_C5, 4,
    NOTE_A4, 4,
    NOTE_G4, 4,
    NOTE_A4, 4,

    NOTE_D5, 4,
    NOTE_B4, 4,
    NOTE_C5, 2,
};

SpeakerManager _speakerManager(SPEAKER_PIN);

void setup() {

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Christmas Tree");
    Board.SetPinMode(SPEAKER_PIN, OUTPUT);
    Board.SetPinMode(SWITCH_PIN, INPUT);
    //Board.SetPinMode(RED_LED_1_PIN, OUTPUT);
    //Board.SetPinMode(GREEN_LED_1_PIN, OUTPUT);
    
    _speakerManager.PlaySequence(ArraySize(pivolDeNuitSeq01), pivolDeNuitSeq01);
}

void PowerOff() {

    //Board.LedOn(RED_LED_1_PIN  , false);
    //Board.LedOn(GREEN_LED_1_PIN, false);
}
void PowerOn() {

    //Board.LedOn(RED_LED_1_PIN, true);
    //Board.LedOn(GREEN_LED_1_PIN, true);
}
void PowerLed(int state) {

    switch (state) {
        case 0:PowerOff(); break;
        case 1:
            //Board.LedOn(RED_LED_1_PIN, false);
            //Board.LedOn(GREEN_LED_1_PIN, true);
            break;
        case 2:PowerOn(); break;
        case 3:
            //Board.LedOn(RED_LED_1_PIN, true);
            //Board.LedOn(GREEN_LED_1_PIN, false);
            break;
    }
}

void AnimateLeds() {

    ledState += 1;
    if (ledState >= MAX_LED_STATE) {
        ledState = 0;
    }
    PowerLed(ledState);
}
void loop() {
    /*
    if (_speakerManager.BackGroundOn) {

        _speakerManager.BackGroundUpdate();
    }
    else {
        PowerOff();
        ledState = 0;
        Board.Delay(1000 * 4);
        PowerLed(ledState);
        _speakerManager.StartSequenceBackGround(ArraySize(WeWishYouAMerryChristmas), WeWishYouAMerryChristmas);
    }

    */
    
    boolean buttonPressed = Board.GetButtonStateDebounced(SWITCH_PIN, _buttonLastStateInLoop);
    if (buttonPressed == true && _buttonLastStateInLoop == false) {
             
        PowerOff();
        ledState = 0;
        PowerLed(ledState);
        _speakerManager.StartSequenceBackGround(ArraySize(WeWishYouAMerryChristmas), WeWishYouAMerryChristmas);
    }
    else {
        if (_speakerManager.BackGroundOn) {

            AnimateLeds();
            _speakerManager.BackGroundUpdate();
        }
    }
    _buttonLastStateInLoop = buttonPressed;
    
}

