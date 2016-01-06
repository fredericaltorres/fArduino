/*

*/
#include <Adafruit_NeoPixel.h>
#include "fArduino.h"
#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);

#define MOTION_SENSOR_PIN 2

RadioShackPIRSensor motionSensor(MOTION_SENSOR_PIN);
#define NEO_PIXEL_PIN_0  3  
#define MAX_LED 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAX_LED, NEO_PIXEL_PIN_0, NEO_GRB + NEO_KHZ800);
#define DEFAULT_BRIGTNESS   32
int _ledBrightness = DEFAULT_BRIGTNESS;

TimeOut _timeOut(500);

/*
Input a value 0 to 255 to get a color value.
The colours are a transition r - g - b - back to r.
Green       : 00..25
Yellow      : 26..50
Red         : 50..85
Pink        : 86..135
Blue        : 136..200
Blue/Green  : 200..256
*/
uint32_t Wheel(byte WheelPos) {

    if (WheelPos < 85) {
        //                 84*3:252 \     255-(84*3):3 /
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

void setup(void)
{
    // start serial port
    Board.Delay(500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Baptiste Alarm");
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    Board.SetPinMode(MOTION_SENSOR_PIN, INPUT);

    _onBoardLed.SetBlinkMode(500);
    strip.setBrightness(_ledBrightness);
    strip.begin();
    strip.show();
}

bool drawLine(uint32_t forwardColor, int wait, int decrease, int minWait, bool backMode, uint32_t backColor) {

    int waitOriginal = wait;
    int numPixels = strip.numPixels();

    for (int i = 0; i < numPixels; i++) {

        strip.setPixelColor(i, forwardColor); // Turn every third pixel on
        strip.show();
        delay(wait);
        if (decrease) {
            wait -= decrease;
            if (wait < minWait)
                wait = minWait;
        }
    }
    if (backMode) {

        delay(waitOriginal);
        for (int i = numPixels - 1; i >= 0; i--) {

            strip.setPixelColor(i, backColor);    // turn every third pixel on
            if (i < numPixels - 1) { // Turn the last one on off
                strip.setPixelColor(i + 1, 0);
            }
            strip.show();
            delay(wait);
            if (decrease) {
                wait += decrease;
                if (wait > waitOriginal)
                    waitOriginal = wait;
            }
        }
        strip.setPixelColor(0, 0);
        delay(waitOriginal);
    }
    return true;
}

void rainbowCycle(uint8_t wait) {

    Board.SendWindowsConsoleCommand(StringFormat.Format("rainbowCycle wait:%d", wait));
    uint16_t i, j;
    for (j = 0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
        for (i = 0; i< strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        delay(wait);
        strip.show();
    }
}

void LightUpLeds(uint16_t j) {

    uint16_t i;
    for (i = 0; i< strip.numPixels(); i++) {

        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
}

void loop(void)
{
    _onBoardLed.Blink();
    
    uint16_t j;
    int wait = 10;

    for (j = 0; j< 256; j++) {

        LightUpLeds(j);
        delay(wait);
        if (_timeOut.IsTimeOut()) {

            Board.Trace(StringFormat.Format("motion %d", digitalRead(MOTION_SENSOR_PIN)));
            if (motionSensor.MotionDetected()) {
                Board.Trace("Motion Detected");
                drawLine(strip.Color(96, 0, 0), 32, false, 10, true, strip.Color(254, 0, 0));
            }
        }
    }
}