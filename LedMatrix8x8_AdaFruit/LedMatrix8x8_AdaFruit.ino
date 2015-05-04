/***************************************************
This is a library for our I2C LED Backpacks

Designed specifically to work with the Adafruit LED Matrix backpacks
----> http://www.adafruit.com/products/872
----> http://www.adafruit.com/products/871
----> http://www.adafruit.com/products/870

These displays use I2C to communicate, 2 pins are required to
interface. There are multiple selectable I2C addresses. For backpacks
with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
with 3 Address Select pins: 0x70 thru 0x77

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, all text above must be included in any redistribution
****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
    Serial.begin(9600);
    Serial.println("8x8 LED Matrix Test");

    matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
B01000010,
B10100101,
B10000001,
B10100101,
B10011001,
B01000010,
B00111100 },
neutral_bmp[] =
{ B00111100,
B01000010,
B10100101,
B10000001,
B10111101,
B10000001,
B01000010,
B00111100 },
frown_bmp[] =
{ B00111100,
B01000010,
B10100101,
B10000001,
B10011001,
B10100101,
B01000010,
B00111100 };

int wait = 200;

void IncreaseDecreaseBrigthness() {
    for (byte b = 0; b < 3; b++) {
        matrix.setBrightness(b + 1);
        delay(wait / 2);
    }
    for (byte b = 2; b > 0; b--) {
        matrix.setBrightness(b + 1);
        delay(wait*2);
    }
}


void Intro() {

    matrix.clear();
    matrix.writeDisplay();  // write the changes we just made to the display
    matrix.drawRect(0, 0, 8, 8, LED_ON);
    matrix.setBrightness(0);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(wait);

    int wait2 = wait;

    for (byte z = 0; z < 5; z++) {

        matrix.clear();
        matrix.drawRect(0, 0, 8, 8, LED_ON);
        matrix.drawRect(2, 2, 4, 4, LED_ON);
        matrix.writeDisplay();  // write the changes we just made to the display
        delay(wait2); wait2 -= 15;
        matrix.clear();
        matrix.drawRect(0, 0, 8, 8, LED_ON);
        matrix.fillRect(3, 3, 2, 2, LED_ON);
        matrix.writeDisplay();  // write the changes we just made to the display
        delay(wait2); wait2 -= 15;
    }
    matrix.clear();
    matrix.drawRect(0, 0, 8, 8, LED_ON);
    matrix.drawRect(1, 1, 6, 6, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(wait / 4);
    matrix.fillRect(0, 0, 8, 8, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(wait);

    IncreaseDecreaseBrigthness();

    matrix.clear();
    matrix.writeDisplay();  // write the changes we just made to the display
    delay(wait * 2);
}

#define SCROLLTEXT_SPEED 60//90

void ScrollText(char *text, int8_t step) {

    matrix.setTextSize(0);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);

    for (int8_t x = 0; x >= -127; x--) {
        matrix.clear();
        matrix.setCursor(x, 0);
        matrix.print(text);
        matrix.writeDisplay();
        delay(SCROLLTEXT_SPEED);
    }
    /*for (int8_t x = -127; x <= 0; x++) {
        matrix.clear();
        matrix.setCursor(x, 0);
        matrix.print(text);
        matrix.writeDisplay();
        delay(SCROLLTEXT_SPEED/3);
    }*/
}

void loop() {

    matrix.setBrightness(3);
    matrix.clear();
    matrix.writeDisplay();  // write the changes we just made to the display
    Intro();    
    char * text = " RESONE - Suite 2015 ";
    ScrollText(text, 127);
    delay(1000);
    text = " Service Store ";
    ScrollText(text, 90);
    delay(1000);
    text = " Workspace ";
    ScrollText(text, 90);
    delay(1000);
    text = " Automation ";
    ScrollText(text, 90);
    delay(1000);    
}

/*matrix.setRotation(3);
for (int8_t x = 7; x >= -36; x--) {
matrix.clear();
matrix.setCursor(x, 0);
matrix.print("World");
matrix.writeDisplay();
delay(100);
}
matrix.setRotation(0);*/

/*

matrix.clear();
matrix.drawCircle(3, 3, 3, LED_ON);
matrix.writeDisplay();  // write the changes we just made to the display
delay(500);

*/

/*matrix.clear();

matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
matrix.writeDisplay();
delay(500);

matrix.clear();
matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
matrix.writeDisplay();
delay(500);

matrix.clear();
matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
matrix.writeDisplay();
delay(500);*/


//for (int r = 0; r < 8; r++) {
//    for (int c = 0; c < 8; c++) {
//        matrix.drawPixel(r, c, LED_ON);
//        matrix.writeDisplay();  // write the changes we just made to the display
//        delay(6);
//    }
//}
// 
//matrix.clear();
//matrix.drawLine(0, 0, 7, 7, LED_ON);
//matrix.writeDisplay();  // write the changes we just made to the display
//delay(500);