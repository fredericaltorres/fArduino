///*
//http://www.tweaking4all.com/hardware/arduino/arduino-ws2812-led/
//*/
//
//#include <Adafruit_NeoPixel.h>
//#include <fArduino.h>
//
//#define ON_BOARD_LED 2
//Led _onBoardLed(ON_BOARD_LED);
//TimeOut _monitorTimeOut(1000);
//
//#define PIN 6
//#define MAX_LED 7
//
//// Parameter 1 = number of pixels in strip
//// Parameter 2 = pin number (most are valid)
//// Parameter 3 = pixel type flags, add together as needed:
////   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
////   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
////   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
////   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAX_LED, PIN, NEO_GRB + NEO_KHZ800);
//
//// Fill the dots one after the other with a color
//void colorWipe(uint32_t c, uint8_t wait) {
//
//    for (uint16_t i = 0; i<strip.numPixels(); i++) {
//
//        strip.setPixelColor(i, c);
//        strip.show();
//        delay(wait);
//    }
//}
//
//void rainbow(uint8_t wait) {
//
//    uint16_t i, j;
//
//    for (j = 0; j<256; j += 4) {
//
//        for (i = 0; i<strip.numPixels(); i++) {
//
//            Board.Trace(StringFormat.Format("j:%d, i:%d, (i + j) & 255:%d", j, i, (i + j) & 255));
//            strip.setPixelColor(i, Wheel((i + j) & 255));
//        }
//        strip.show();
//        delay(wait);
//    }
//}
//
//const byte flameWaitPattern[] = {//PROGMEM
//    10, 14, 18, 22, 24, 22, 18, 14, 10,
//    10, 15, 20, 25, 20, 15, 10, 5, 1,
//    10, 16, 18, 24, 20, 16, 14, 12, 10,
//};
//#define flameWaitPatternSize (9*3)
//
//void fire(uint8_t wait, uint8_t fireStart, uint8_t fireEnd) {
//
//    uint16_t i, j;
//    uint16_t fireRandomStepMax = 12;
//    uint16_t fireRandomSleepMax = 25;
//    uint16_t fireRandomSleepMin = 10;
//    uint16_t fireRandomSleep = 0;
//    uint16_t step = 0;
//    uint16_t flameWaitPatternIndex = 0;
//    j = fireStart;
//    while (j < fireEnd) {
//
//        step = 1;
//        for (i = 0; i<strip.numPixels(); i++) {
//            strip.setPixelColor(i, Wheel((i + j) & 255));
//        }
//        strip.show();
//        int w = flameWaitPattern[flameWaitPatternIndex] * 5 / 2;
//        delay(w);
//        flameWaitPatternIndex++;
//        if (flameWaitPatternIndex >= flameWaitPatternSize) flameWaitPatternIndex = 0;
//        //Board.Trace(StringFormat.Format("up> j:%d, step:%d, w:%d", j, step, w));
//        j += step;
//    }
//    delay(random(10, 40));
//    flameWaitPatternIndex = 0;
//    j = fireEnd;
//    while (j >= fireStart) {
//
//        step = 1;
//        for (i = 0; i<strip.numPixels(); i++) {
//            strip.setPixelColor(i, Wheel((i + j) & 255));
//        }
//        strip.show();
//        int w = flameWaitPattern[flameWaitPatternIndex] * 5 / 2;
//        delay(w);
//        flameWaitPatternIndex++;
//        if (flameWaitPatternIndex >= flameWaitPatternSize) flameWaitPatternIndex = 0;
//        //Board.Trace(StringFormat.Format("down> j:%d, step:%d, w:%d", j, step, w));
//        j -= step;
//    }
//    delay(random(10, 40));
//    delay(random(10, 40));
//}
//
//// Slightly different, this makes the rainbow equally distributed throughout
//void rainbowCycle(uint8_t wait) {
//
//    uint16_t i, j;
//
//    for (j = 0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
//
//        for (i = 0; i< strip.numPixels(); i++) {
//
//            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//        }
//        strip.show();
//        delay(wait);
//    }
//}
//
////Theatre-style crawling lights.
//void theaterChase(uint32_t c, uint8_t wait) {
//
//    for (int j = 0; j<10; j++) {  //do 10 cycles of chasing
//
//        for (int q = 0; q < 3; q++) {
//
//            for (int i = 0; i < strip.numPixels(); i = i + 3) {
//
//                strip.setPixelColor(i + q, c);    //turn every third pixel on
//            }
//            strip.show();
//            delay(wait);
//            for (int i = 0; i < strip.numPixels(); i = i + 3) {
//                strip.setPixelColor(i + q, 0);        //turn every third pixel off
//            }
//        }
//    }
//}
//
////Theatre-style crawling lights with rainbow effect
//void theaterChaseRainbow(uint8_t wait) {
//
//    for (int j = 0; j < 256; j++) {     // cycle all 256 colors in the wheel
//
//        for (int q = 0; q < 3; q++) {
//
//            for (int i = 0; i < strip.numPixels(); i = i + 3) {
//
//                strip.setPixelColor(i + q, Wheel((i + j) % 255));    //turn every third pixel on
//            }
//            strip.show();
//            delay(wait);
//            for (int i = 0; i < strip.numPixels(); i = i + 3) {
//
//                strip.setPixelColor(i + q, 0);        //turn every third pixel off
//            }
//        }
//    }
//}
//
//// Input a value 0 to 255 to get a color value.
//// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//
//    if (WheelPos < 85) {
//        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//    }
//    else if (WheelPos < 170) {
//        WheelPos -= 85;
//        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//    }
//    else {
//        WheelPos -= 170;
//        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//    }
//}
//
//void setup() {
//
//    Board.Delay(1500); // Wait 1.5 second before initializing the serial com, so  I can start the ArduinoWindowsConsole on the Windows machine
//
//    Board.InitializeComputerCommunication(9600, "Initializing...");
//    Board.TraceHeader("NeoPixel 1");
//
//    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
//
//    _onBoardLed.SetBlinkMode(1000);
//
//    strip.begin();
//    strip.show(); // Initialize all pixels to 'off'
//    strip.setBrightness(40);
//}
//
//void loop() {
//
//    //rainbow(40);
//    randomSeed(analogRead(0));
//    _onBoardLed.Blink(); // Blink led every 1/2 second
//    Board.Trace("rainbow");
//    fire(5, 40, 74); // Yellow to Red
//    //fire(5, 155, 200); // Blue dark to blue light
//    return;
//
//    //Board.TraceHeader("colorWipe full demo");
//    //for (int cc = 0; cc < 255; cc++) {
//    //    byte r = cc;
//    //    byte g = 255 - cc;
//    //    byte b = 0;// (byte)((255 / 2) - cc);
//    //    colorWipe(strip.Color(r, g, b), 5); // Red
//    //    Board.Trace(StringFormat.Format("r:%d, g:%d, b:%d", r, g, b));
//    //}
//    //return;
//
//    // Some example procedures showing how to display to the pixels:
//    Board.Trace("colorWipe red");
//    colorWipe(strip.Color(255, 0, 0), 50); // Red
//
//    Board.Trace("colorWipe Green");
//    colorWipe(strip.Color(0, 255, 0), 50); // Green
//
//    Board.Trace("colorWipe Blue");
//    colorWipe(strip.Color(0, 0, 255), 50); // Blue
//
//    // Send a theater pixel chase in...
//    Board.Trace("theaterChase white");
//    theaterChase(strip.Color(127, 127, 127), 50); // White
//    Board.Trace("theaterChase red");
//    theaterChase(strip.Color(127, 0, 0), 50); // Red
//    Board.Trace("theaterChase blue");
//    theaterChase(strip.Color(0, 0, 127), 50); // Blue
//
//    Board.Trace("rainbow");
//    rainbow(20);
//
//    Board.Trace("rainbowCycle");
//    rainbowCycle(20);
//
//    Board.Trace("theaterChaseRainbow");
//    theaterChaseRainbow(50);
//
//    // Process commands coming from the WindowsConsole
//    WindowsCommand winCommand = Board.GetWindowsConsoleCommand(); // The WindowsConsole method use the Serial port communication
//
//    if (winCommand.Command == "read") {
//
//        Board.SendWindowsConsoleCommand("Read");
//    }
//    else if (winCommand.Command == "write") {
//
//        Board.SendWindowsConsoleCommand("Write");
//    }
//    else {
//        if (winCommand.Command != "") {
//            Board.SendWindowsConsoleCommand(StringFormat.Format("[Invalid command:%s]", winCommand.Command.c_str()));
//        }
//    }
//}
