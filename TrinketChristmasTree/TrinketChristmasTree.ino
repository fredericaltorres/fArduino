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


    Transistor Amplification - Arduino Workshop Project Video #2
    https://www.youtube.com/watch?v=cEz1i5xzGEE#t=14

***************************************************************************/

#include "fArduino.h"

// Pins Usage

#define RED_LED_ONBAORD_PIN     13

#define SPEAKER_PIN             3 // Need PWM
#define RED_LED_PIN             4
#define GREEN_LED_1_PIN         5
#define GREEN_LED_2_PIN         6
#define SWITCH_PIN              7

// Define/Keep track of 4 states to display the 3 leds (1 Red Led and 2 Greens Led coupled together)
int _ledStateIndex = 0; // 0..11

// If we are not playing, let's animate the leds every x seconds
#define ANIMATE_LED_EVERY_X_SECOND 6

// Keep track if the last time we played the song or animate the led
long    _lastTimePlayedOrAnimate = 0;


// Define music to start or stop something
#define FACTOR 4
int musicStart[] = { NOTE_E4, 8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_A4, 8 * FACTOR, NOTE_B4, 8 * (FACTOR/2) };
int musicEnd[]   = { NOTE_B4,  8 * FACTOR, NOTE_A4,  8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_E4,  8 * (FACTOR/2) };

// http://www.unimusica-peru.com/partit21.gif

#if defined(ARDUINO_UNO) 
    // Sound better on a Arduino UNO
    int WeWishYouAMerryChristmas[] = {

        NOTE_G2, 4, NOTE_C3, 4, NOTE_C3, 8, NOTE_D3, 8, NOTE_C3, 8, NOTE_B2, 8, NOTE_A2, 2,
        NOTE_A2, 4, NOTE_D3, 4, NOTE_D3, 8, NOTE_E3, 8, NOTE_D3, 8, NOTE_C3, 8, NOTE_B2, 2, NOTE_G2, 4,
        NOTE_E3, 4, NOTE_E3, 8, NOTE_F3, 8, NOTE_E3, 8, NOTE_D3, 8, NOTE_C3, 4, NOTE_A2, 4, NOTE_G2, 4, NOTE_A2, 4,
        NOTE_D3, 4, NOTE_B2, 4, NOTE_C3, 2,
    };
#else
    // Sound bette on a Trinket at 8Mhz
    int WeWishYouAMerryChristmas[] = {
    
        NOTE_G4, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 8, NOTE_A4, 2,
        NOTE_A4, 4, NOTE_D5, 4, NOTE_D5, 8, NOTE_E5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 2, NOTE_G4, 4,
        NOTE_E5, 4, NOTE_E5, 8, NOTE_F5, 8, NOTE_E5, 8, NOTE_D5, 8, NOTE_C5, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_A4, 4,
        NOTE_D5, 4, NOTE_B4, 4, NOTE_C5, 2,
    };
#endif

SpeakerManager  _speakerManager(SPEAKER_PIN);
Led             _onBoardLed(RED_LED_ONBAORD_PIN);
PullUpButton    _button(SWITCH_PIN);

void setup() {

    Board.Delay(1500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Christmas Tree");
    Board.SetPinMode(SPEAKER_PIN   , OUTPUT);
    Board.SetPinMode(RED_LED_ONBAORD_PIN, OUTPUT);
    
    //Board.SetPinMode(SWITCH_PIN    , INPUT);
    Board.SetPinMode(RED_LED_PIN    , OUTPUT);
    Board.SetPinMode(GREEN_LED_1_PIN, OUTPUT);
    Board.SetPinMode(GREEN_LED_2_PIN, OUTPUT);
    // SWITCH_PIN is initialized already as pull up by consttructor of PullUpButton
    PowerOff();

    _onBoardLed.SetBlinkMode(1000);
    _speakerManager.PlaySequence(ArraySize(musicStart), musicStart);
    _speakerManager.BackGroundOn = false;
}

#define LEDS_ALL_OFF 0
#define LEDS_ALL_ON 10

void PowerOn() {

    PowerLed(LEDS_ALL_ON);
}
void PowerOff() {

    _ledStateIndex = 0;
    PowerLed(_ledStateIndex);
}
void PowerLeds(boolean valueR, boolean valueG1, boolean valueG2) {

    Board.LedOn(RED_LED_PIN    , valueR);
    Board.LedOn(GREEN_LED_1_PIN, valueG1);
    Board.LedOn(GREEN_LED_2_PIN, valueG2);
}

int _ledStateProgram[] = { 
    1, // Red
    4, // Red + Green1
   10, // Red + Green1 + Green2
    0, // All Off
   10, // Red + Green1 + Green2
    0, // All Off
   10, // Red + Green1 + Green2
    4, // Red + Green1
    1, // Red
    0, // All Off
};

#define MAX_LED_STATE ArraySize(_ledStateProgram)

void PowerLedProgram(int stateIndex) {

    int state = _ledStateProgram[stateIndex];
    PowerLed(state);
}

void PowerLed(int state) {
    
    switch (state) {

        case  0: PowerLeds(false, false, false); break; // All Off
        case  1: PowerLeds(true , false, false); break; // 1 on
        case  2: PowerLeds(false, true,  false); break;
        case  3: PowerLeds(false, false, true ); break;
        case  4: PowerLeds(true,  true , false); break; // 2 on
        case  5: PowerLeds(true , false, true ); break;
        case  6: PowerLeds(false, true , true ); break;
        case  7: PowerLeds(true , true , false); break;
        case  8: PowerLeds(false, true , true ); break;
        case  9: PowerLeds(true , false, true ); break;
        case 10: PowerLeds(true,  true,  true ); break; // All On
    }
}
bool WaitForAnimation(int index) {

    for (int i = 0; i < 5; i++) {
        Board.Delay(50);
        if (_button.IsPressed()) {
            Board.Trace("Pressed A");
            return true;
        }
    }
    return false;
}
boolean LedsAnimationAllOnAllOff() {

    for (int i = 0; i < 10; i++) {

        PowerOff(); 
        if (WaitForAnimation(i)) return true;
        PowerOn();
        if (WaitForAnimation(i)) return true;
    }
    PowerOff();
    return false;
}
boolean LedsRandomAnimation() {
  
    static int _counter;
    boolean r = false;

    if(_counter == 0)
        r = LedsAnimationAllOnAllOff();
    else if(_counter == 1)
        r = LedsAnimationAllOnAllOff();
    else if(_counter == 2)
        r = LedsAnimationAllOnAllOff();
    
    if ((_counter++) > 2)
        _counter = 0;

    PowerOff();

    return r;
}
void AnimateLedsWhilePaying() {

    _ledStateIndex += 1;
    if (_ledStateIndex >= MAX_LED_STATE)
        _ledStateIndex = 0;
    PowerLedProgram(_ledStateIndex);
}

void StartMusicAnimation() {

    Board.Trace("Start animation");
    PowerOff();
    _ledStateIndex = -1;

    Board.Delay(100); // To void button boucing

    AnimateLedsWhilePaying();
    _speakerManager.StartSequenceBackGround(ArraySize(WeWishYouAMerryChristmas), WeWishYouAMerryChristmas);
}

void loop() {

    _onBoardLed.Blink(); // Blink ebery seconds
    
    if (_button.IsPressed()) {
        
        if (_speakerManager.BackGroundOn) {

            _speakerManager.StopBackGroundSequence();
            Board.Trace("Sequence Stopped");
            Board.Delay(100); // To void button boucing
        }
        else {
            StartMusicAnimation();
        }
    }
    else {
        if (_speakerManager.BackGroundOn) {

            AnimateLedsWhilePaying();
            if (!_speakerManager.BackGroundUpdate()) {

                boolean ar = LedsRandomAnimation(); // We reach the end of the song
                _lastTimePlayedOrAnimate = millis();                
                if (ar) {
                    StartMusicAnimation();
                }
            }
        }
        else {                                                    
            // If we are not playing
            // and we did not play in the last 10 seconds, execute a random animation
            if (millis() - _lastTimePlayedOrAnimate > ANIMATE_LED_EVERY_X_SECOND * 1000) {
                
                boolean ar = LedsRandomAnimation(); // We reach the end of the song
                _lastTimePlayedOrAnimate = millis();
                if (ar) {
                    StartMusicAnimation();
                }
            }
        }
    }
}
