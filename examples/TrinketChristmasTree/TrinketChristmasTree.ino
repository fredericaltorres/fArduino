/*************************************************************************

    Christmas Tree Animation With A Trinket MicroController
    
    Functionality:
        (1) Play a short music when starting
        (2) While idle execute 3 differents leds animation every 6 seconds
        (3) If user press button play or stop "we wish you a merry christmas"

    Remarks:
        - Must be compiled at 8Mhz on a Trinket mini
        - Can be compiled on an Arduino Uno 


    Torres Frederic 2014.12, 2015.01

***************************************************************************/

#include "fArduino.h"

// Pins Usage
 
#if ARDUINO_UNO
    #define RED_LED_ONBAORD_PIN     13
    #define SPEAKER_PIN             3 // PWM, Purple wire
    #define RED_LED_PIN             4 // Yellow wire
    #define GREEN_LED_1_PIN         5 // Blue wire
    #define GREEN_LED_2_PIN         6 // Orange wire
    #define SWITCH_PIN              7 // White wire
#endif
#if TRINKET
    
    #define SPEAKER_PIN             0 // PWM, Purple wire
    #define RED_LED_PIN             1 // Yellow wire
    #define SWITCH_PIN              2 // White wire
    #define GREEN_LED_1_PIN         3 // Blue wire
    #define GREEN_LED_2_PIN         4 // Orange wire
#endif

// Define/Keep track of 11 states to display the 6 leds (2 Red Led, 2 Greens and 2 greens)
int _ledStateIndex = 0; // 0..11

// If we are not playing, let's animate the leds every x seconds
#define ANIMATE_LED_EVERY_X_SECOND 6

// Keep track of the last time we played the song or animate the leds
long _lastTimePlayedOrAnimate = 0;

// Define music to start or stop something
#define FACTOR 4
int musicStart[] = { NOTE_E4, 8 * FACTOR , NOTE_FS4, 8 * FACTOR, NOTE_A4 , 8 * FACTOR, NOTE_B4, 8 * (FACTOR/2) };
int musicEnd[]   = { NOTE_B4,  8 * FACTOR, NOTE_A4 , 8 * FACTOR, NOTE_FS4, 8 * FACTOR, NOTE_E4, 8 * (FACTOR/2) };

// We wish you a merry christmas (By the way I am not a beleiver)
// http://www.unimusica-peru.com/partit21.gif
//
#if defined(ARDUINO_UNO) 
    int WeWishYouAMerryChristmas[] = { // Sound better on a Arduino UNO

        NOTE_G2, 4, NOTE_C3, 4, NOTE_C3, 8, NOTE_D3, 8, NOTE_C3, 8, NOTE_B2, 8, NOTE_A2, 2,
        NOTE_A2, 4, NOTE_D3, 4, NOTE_D3, 8, NOTE_E3, 8, NOTE_D3, 8, NOTE_C3, 8, NOTE_B2, 2, NOTE_G2, 4,
        NOTE_E3, 4, NOTE_E3, 8, NOTE_F3, 8, NOTE_E3, 8, NOTE_D3, 8, NOTE_C3, 4, NOTE_A2, 4, NOTE_G2, 4, NOTE_A2, 4,
        NOTE_D3, 4, NOTE_B2, 4, NOTE_C3, 2,
    };
#else
    int WeWishYouAMerryChristmas[] = { // Sound better on a Trinket at 8Mhz
    
        NOTE_G4, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 8, NOTE_A4, 2,
        NOTE_A4, 4, NOTE_D5, 4, NOTE_D5, 8, NOTE_E5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4, 2, NOTE_G4, 4,
        NOTE_E5, 4, NOTE_E5, 8, NOTE_F5, 8, NOTE_E5, 8, NOTE_D5, 8, NOTE_C5, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_A4, 4,
        NOTE_D5, 4, NOTE_B4, 4, NOTE_C5, 2,
    };
#endif

SpeakerManager  _speakerManager(SPEAKER_PIN);
PullUpButton    _button(SWITCH_PIN);

#if ARDUINO_UNO
    Led _onBoardLed(RED_LED_ONBAORD_PIN);
#endif
    
#define LEDS_ALL_OFF  0
#define LEDS_ALL_ON  10

void PowerOn() {

    PowerLed(LEDS_ALL_ON);
}
void PowerOff() {

    _ledStateIndex = 0; // Reset program index
    PowerLed(_ledStateIndex);
}
void PowerLeds(boolean valueR, boolean valueG1, boolean valueG2) {

    Board.LedOn(RED_LED_PIN    , valueR);
    Board.LedOn(GREEN_LED_1_PIN, valueG1);
    Board.LedOn(GREEN_LED_2_PIN, valueG2);
}
int _ledsStateProgram[] = { 

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
#define LED_STATE_PROGRAM_LENGTH ArraySize(_ledsStateProgram)

void PowerLedProgram(int programIndex) {

    if (programIndex >= 0 && programIndex < LED_STATE_PROGRAM_LENGTH) {
        int state = _ledsStateProgram[programIndex];
        PowerLed(state);
    }
    else {
        Board.Trace("PowerLedProgram() was passed an invalid programIndex");
    }
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
            return true;
        }
    }
    return false;
}
boolean LedsAnimationAllOnAllOff() {

    boolean r = false;
    for (int i = 0; i < 7; i++) {

        PowerOff();
        if (WaitForAnimation(i)) { r = true; break; }
        PowerOn();
        if (WaitForAnimation(i)) { r = true; break; }
    }
    PowerOff();
    return r;
}
boolean LedsAnimationUpAndDown() {

    int upAndDownProgram[] = {        
        1, // Red
        4, // Red + Green1
        10, // Red + Green1 + Green2
        10, // Red + Green1 + Green2        
        4, // Red + Green1
        1, // Red
        0, // All Off
        0, // All Off
    };

    boolean r = false;

    for (int count = 0; count < 3; count++) {

        for (int i = 0; i < ArraySize(upAndDownProgram); i++) {

            PowerLed(upAndDownProgram[i]);
            if (WaitForAnimation(i)) { r = true; break; }
        }
    }
    PowerOff();
    return r;
}

boolean LedsAnimationAllOrMiddle() {

    boolean r = false;
    PowerOff();
    for (int i = 0; i < 7; i++) {

        PowerLed(2);
        if (WaitForAnimation(i)) { r = true; break; }
        PowerOn();
        if (WaitForAnimation(i)) { r = true; break; }
    }
    PowerOff();
    return r;
}

boolean LedsRandomAnimation() {
  
    static int _counter;
    boolean r = false;

    if(_counter == 0)
        r = LedsAnimationAllOnAllOff();
    else if(_counter == 1)
        r = LedsAnimationUpAndDown();
    else if(_counter == 2)
        r = LedsAnimationAllOrMiddle(); // TODO: Create new animation
    
    if ((_counter++) > 2)
        _counter = 0;

    PowerOff();

    return r;
}
void AnimateLedsWhilePaying() {

    _ledStateIndex += 1;
    if (_ledStateIndex >= LED_STATE_PROGRAM_LENGTH)
        _ledStateIndex = 0;
    PowerLedProgram(_ledStateIndex);
}
void StartMusicAnimation() {

    PowerOff();
    _ledStateIndex = -1;

    Board.Delay(100); // To avoid button bouncing

    AnimateLedsWhilePaying();
    _speakerManager.StartSequenceBackGround(ArraySize(WeWishYouAMerryChristmas), WeWishYouAMerryChristmas);
}
void setup() {

    Board.Delay(1500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    #if ARDUINO_UNO
    Board.TraceHeader("Christmas Tree - v2");
    #endif  

    Board.SetPinMode(SPEAKER_PIN        , OUTPUT);
    Board.SetPinMode(RED_LED_PIN        , OUTPUT);
    Board.SetPinMode(GREEN_LED_1_PIN    , OUTPUT);
    Board.SetPinMode(GREEN_LED_2_PIN    , OUTPUT);
    #if ARDUINO_UNO
    Board.SetPinMode(RED_LED_ONBAORD_PIN, OUTPUT);
    #endif
    // SWITCH_PIN is initialized already as pull up by consttructor of PullUpButton

    PowerOff();

    #if ARDUINO_UNO
    _onBoardLed.SetBlinkMode(1000);
    #endif
    _speakerManager.PlaySequence(ArraySize(musicStart), musicStart); // Annonce that setup is done
}
void loop() {

    #if ARDUINO_UNO
    _onBoardLed.Blink(); // Blink every seconds
    #endif
    
    if (_button.IsPressed()) {

        if (_speakerManager.BackGroundOn) { // If playing stop playing

            _speakerManager.StopBackGroundSequence();
            Board.Trace("Sequence Stopped");
            Board.Delay(100); // To avoid button bouncing
        }
        else {
            StartMusicAnimation();
        }
    }
    else {
        if (_speakerManager.BackGroundOn) { // Call the Led animation and music 

            AnimateLedsWhilePaying();
            if (!_speakerManager.BackGroundUpdate()) {
                // We reach the end of the song, play a random animation
                boolean ar = LedsRandomAnimation(); 
                _lastTimePlayedOrAnimate = millis();
                if (ar) { // If user ask for music while animating leds start playing
                    StartMusicAnimation();
                }
            }
        }
        else {                                                    
            // If we are not playing
            // and we did not play in the last 6 seconds, execute a random animation
            if (millis() - _lastTimePlayedOrAnimate > ANIMATE_LED_EVERY_X_SECOND * 1000) {
                
                boolean ar = LedsRandomAnimation(); // Play a random animation
                _lastTimePlayedOrAnimate = millis();
                if (ar) { // If user ask for music while animating leds start playing
                    StartMusicAnimation();
                }
            }
        }
    }
}