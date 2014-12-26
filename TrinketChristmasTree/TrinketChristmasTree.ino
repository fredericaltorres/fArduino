/*************************************************************************

    Christmas Tree Animation With A Trinket MicroController

    Using 1 red led and 2 green leds, create a pseudo Christmas Tree animation with music.
    
    Functionality:
        (1) Play a short music when starting
        (2) While idle execute 3 differents leds animation every 6 seconds
        (3) If user press button play "we wish you a merry christmas"

    Remarks:
        - Must be compiled at 8Mhz
        - Because my pin #2 was not working I plugged the 2 green leds to the same pin.

    Torres Frederic 2014.12

***************************************************************************/

#include "fArduino.h"

#define USE_LEDS 1

// Pins Usage
#define RED_LED_ONBAORD_PIN     13
#define SWITCH_PIN              0    
#define SPEAKER_PIN             1
#define RED_LED_PIN             3
#define GREEN_LEDS_PIN          4

// Define/Keep track of 4 states to display the 3 leds (1 Red Led and 2 Greens Led coupled together)
#define MAX_LED_STATE 4
int _ledState = 0; // 0..3

// If we are not playing, let's animate the leds every x seconds
#define ANIMATE_LED_EVERY_X_SECOND 6

// Keep track if the last time we played the song or animate the led
long    _lastTimePlayedOrAnimate = 0;

// Keep track of the last switch button state (debouncing)
boolean _buttonLastStateInLoop = false;

// Define music to start or stop something
#define FACTOR 4
int musicStart[] = { NOTE_E4, 8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_A4, 8 * FACTOR, NOTE_B4, 8 * (FACTOR/2) };
int musicEnd[]   = { NOTE_B4,  8 * FACTOR, NOTE_A4,  8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_E4,  8 * (FACTOR/2) };

// http://www.unimusica-peru.com/partit21.gif

#if defined(ARDUINO_UNO) 
    // Sound better on a Arduino UNO
    int WeWishYouAMerryChristmas_Arduino[] = {

        NOTE_G2, 4, NOTE_C3, 4, NOTE_C3, 8, NOTE_D3, 8, NOTE_C3, 8, NOTE_B2, 8, NOTE_A2, 2,
        NOTE_A2, 4, NOTE_D3, 4, NOTE_D3, 8, NOTE_E3, 8, NOTE_D3, 8, NOTE_C3, 8, NOTE_B2, 2, NOTE_G2, 4,
        NOTE_E3, 4, NOTE_E3, 8, NOTE_F3, 8, NOTE_E3, 8, NOTE_D3, 8, NOTE_C3, 4, NOTE_A2, 4, NOTE_G2, 4, NOTE_A2, 4,
        NOTE_D3, 4, NOTE_B2, 4, NOTE_C3, 2,
    };
#endif

// Sound bette on a Trinket at 8Mhz
int WeWishYouAMerryChristmas[] = {
    
    NOTE_G4, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 8, NOTE_A4, 2,
    NOTE_A4, 4, NOTE_D5, 4, NOTE_D5, 8, NOTE_E5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 2, NOTE_G4, 4,
    NOTE_E5, 4, NOTE_E5, 8, NOTE_F5, 8, NOTE_E5, 8, NOTE_D5, 8, NOTE_C5, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_A4, 4,
    NOTE_D5, 4, NOTE_B4, 4, NOTE_C5, 2,
};

SpeakerManager _speakerManager(SPEAKER_PIN);

void setup() {

    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Christmas Tree");
    Board.SetPinMode(SPEAKER_PIN   , OUTPUT);
    Board.SetPinMode(SWITCH_PIN    , INPUT);
    #if defined(USE_LEDS)
    Board.SetPinMode(RED_LED_PIN   , OUTPUT);
    Board.SetPinMode(GREEN_LEDS_PIN, OUTPUT);
    #endif
    PowerOff();
    _speakerManager.PlaySequence(ArraySize(musicStart), musicStart);
    _speakerManager.BackGroundOn = false;
}
void PowerOn() {

    PowerLed(2);
}
void PowerOff() {

    _ledState = 0;
    PowerLed(_ledState);
}
void PowerLed(int state) {

    #if defined(USE_LEDS)

    switch (state) {
        case 0:
            Board.LedOn(RED_LED_PIN   , false);
            Board.LedOn(GREEN_LEDS_PIN, false);
            break;
        case 1:
            Board.LedOn(RED_LED_PIN   , false);
            Board.LedOn(GREEN_LEDS_PIN, true);
            break;
        case 2:
            Board.LedOn(RED_LED_PIN   , true);
            Board.LedOn(GREEN_LEDS_PIN, true);
            break;
        case 3:
            Board.LedOn(RED_LED_PIN   , true);
            Board.LedOn(GREEN_LEDS_PIN, false);
            break;
    }
    #endif
}
void WaitForAnimation(int index) {
  
  Board.Delay(250);
}
void LedsAnimation1() {

    for (int i = 0; i < 6; i++) {

        PowerOff(); WaitForAnimation(i);
        PowerOn();  WaitForAnimation(i);
    }
    PowerOff();
}
void LedsAnimation2() {

    for (int i = 0; i < 6; i++) {

        PowerLed(1); WaitForAnimation(i);
        PowerLed(3); WaitForAnimation(i);
    }
    PowerOff();
}
void LedsAnimation3() {

    for (int i = 0; i < 6; i++) {

        PowerLed(3); WaitForAnimation(i);
        PowerLed(1); WaitForAnimation(i);
    }
    PowerOff();
}
void LedsRandomAnimation() {
  
    static int _counter;

    // If I use the ramdomSeed() and/or random() function, the deployment on the Trinket fail
    // if (random(100) % 2 == 0)

    if(_counter == 0)
        LedsAnimation1();
    else if(_counter == 1)
      LedsAnimation2();
    else if(_counter == 2)
      LedsAnimation3();
    
    if ((_counter++) > 2)
        _counter = 0;
}
void AnimateLedsWhilePaying() {

    _ledState += 1;
    if (_ledState >= MAX_LED_STATE)
        _ledState = 0;
    PowerLed(_ledState);
}
void loop() {
    /*
    if (_speakerManager.BackGroundOn) 
        _speakerManager.BackGroundUpdate();
    else 
        _speakerManager.StartSequenceBackGround(ArraySize(WeWishYouAMerryChristmas), WeWishYouAMerryChristmas);
    return;
    */

    /*
    boolean buttonPressed = Board.GetButtonStateDebounced(SWITCH_PIN, _buttonLastStateInLoop);
    if (buttonPressed == true && _buttonLastStateInLoop == false) {

        _speakerManager.PlaySequence(ArraySize(musicStart), musicStart);
    }
    _buttonLastStateInLoop = buttonPressed;
    */
    
    boolean buttonPressed = Board.GetButtonStateDebounced(SWITCH_PIN, _buttonLastStateInLoop);

    if (buttonPressed == true && _buttonLastStateInLoop == false) {
        
        PowerOn();
        _speakerManager.StartSequenceBackGround(ArraySize(WeWishYouAMerryChristmas), WeWishYouAMerryChristmas);
    }
    else {
        if (_speakerManager.BackGroundOn) {

            AnimateLedsWhilePaying();
            if (!_speakerManager.BackGroundUpdate()) {

                LedsRandomAnimation(); // We reach the end of the song
                _lastTimePlayedOrAnimate = millis();
                PowerOff();
            }
        }
        else {                                                    
            // If we are not playing
            // and we did not play in the last 10 seconds, execute a random animation
            if (millis() - _lastTimePlayedOrAnimate > ANIMATE_LED_EVERY_X_SECOND * 1000) {
                
                LedsRandomAnimation();
                _lastTimePlayedOrAnimate = millis();
            }
        }
    }
    _buttonLastStateInLoop = buttonPressed;
}
