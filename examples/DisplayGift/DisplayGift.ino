// LCD5110_Graph_Demo 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of most of the functions
// in the library.
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
// http://www.rinkydinkelectronics.com/t_imageconverter_mono.php
#include "Graphics.h"
#include <LCD5110_Graph.h>

/*
    Pins
        VCC     VCC
        GND     GND 
        SCE     11
        RST     12
        D/C     10
        DN MOSI 9
        CLOCK   8
        LIGHT   GND
*/

LCD5110 myGLCD(8, 9, 10, 12, 11); //LCD5110(int SCK, int MOSI, int DC, int RST, int CS);

extern uint8_t Sarah01[];
extern uint8_t Sarah_WithHands[];
extern uint8_t SarahJimmy[];
extern uint8_t Ally[];
extern uint8_t Kelly_BW[];
extern uint8_t LEA_BW[];
extern uint8_t AllySarahCamera[];
extern uint8_t SarahLea[];
extern uint8_t Anna2[];
extern uint8_t Anna[];
extern uint8_t SarahAllyPool[];
extern uint8_t Sarah10[];
extern uint8_t SarahAllyLea[];
extern uint8_t Graduating[];
extern uint8_t Graduating2[];
extern uint8_t Bryant[];
extern uint8_t SarahLaughing[];
extern uint8_t Graduating3[];
extern uint8_t SarahOneMore[];
extern uint8_t SarahTopModel[];

extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
extern uint8_t The_End[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];

float y;
uint8_t* bm;
int pacy;

#define FAST 2

#define ON_BOARD_LED 13

void __delay(int wait) {

    digitalWrite(ON_BOARD_LED, HIGH);
    delay(wait);
    digitalWrite(ON_BOARD_LED, LOW);
}


void setup()
{
    myGLCD.InitLCD();
    myGLCD.setFont(SmallFont);
    randomSeed(analogRead(7));

    pinMode(ON_BOARD_LED, OUTPUT);
}

void DisplayImage(uint8_t image[], int wait)  {

    myGLCD.clrScr();
    myGLCD.drawBitmap(0, 0, image, 84, 48);
    myGLCD.update();
    __delay(wait / FAST);
}


void LogoMessage(char * m1, char * m2, char * m3, int wait, int waitAnim)  {
    
    myGLCD.setFont(SmallFont);
    myGLCD.clrScr();
    myGLCD.drawRect(0, 0, 84 - 1, 48 - 1);
    myGLCD.update(); __delay(waitAnim);

    int x = 6;
    myGLCD.print(m1, CENTER, x); myGLCD.update(); __delay(waitAnim);
    x += 14;
    myGLCD.print(m2, CENTER, x); myGLCD.update(); __delay(waitAnim);
    x += 14;
    myGLCD.print(m3, CENTER, x); myGLCD.update(); __delay(waitAnim);
        
    //myGLCD.setFont(TinyFont); myGLCD.print("Sarah McCowan", CENTER, 42);
    myGLCD.update();
    __delay(wait / FAST);
}


void Transition1() {

    myGLCD.clrScr();
    for (int i = 0; i<48; i += 4)
    {
        myGLCD.drawLine(0, i, 83, 47 - i);
        myGLCD.update();
    }
    for (int i = 83; i >= 0; i -= 4)
    {
        myGLCD.drawLine(i, 0, 83 - i, 47);
        myGLCD.update();
    }
    __delay(750 /  FAST);

}

void Transition2() {

    myGLCD.clrScr();
    myGLCD.drawRect(0, 0, 83, 47);
    for (int i = 0; i<48; i += 4)
    {
        myGLCD.drawLine(0, i, i*1.75, 47);
        myGLCD.update();
    }
    for (int i = 0; i<48; i += 4)
    {
        myGLCD.drawLine(83, 47 - i, 83 - (i*1.75), 0);
        myGLCD.update();
    }
    __delay(750 / FAST);
}

void Transition3() {

    myGLCD.clrScr();
    int step = 2;
    for (int i = 0; i < 12; i+=1)
    {
        myGLCD.drawRoundRect(i * step, i * step, 83 - (i * step), 47 - (i * step));
        myGLCD.update();
        __delay(10);
    }

    __delay(750 / FAST);
}

void Transition4() {

    myGLCD.clrScr();
    for (int i = 0; i < 17; i++)
    {
        myGLCD.drawCircle(41, 23, i * 3);
        myGLCD.update();
    }
    __delay(750 / FAST);
}


void ScienceIsGreat() {

    LogoMessage("Science", "Is Great", "...", 4000, 500);

    myGLCD.clrScr();
    myGLCD.drawRect(0, 0, 83, 47);
    myGLCD.drawLine(0, 23, 84, 23);
    myGLCD.drawLine(41, 0, 41, 47);
    for (int c = 0; c < 2; c++)
    {
        for (int i = 0; i < 84; i++)
        {
            y = i*0.017453292519943295769236907684886;
            myGLCD.invPixel(i, (sin(y * 6) * 20) + 23);
            myGLCD.update();
            __delay(11);
        }
    }
    __delay(1000 / FAST);
}


void ScienceIsGreatBackWard() {

    LogoMessage("Science", "Is Great", "...", 4000, 500);

    myGLCD.clrScr();
    myGLCD.drawRect(0, 0, 83, 47);
    myGLCD.drawLine(0, 23, 84, 23);
    myGLCD.drawLine(41, 0, 41, 47);
    for (int c = 0; c < 2; c++)
    {
        for (int i = 84; i > 0; i--)
        {
            y = i*0.017453292519943295769236907684886;
            myGLCD.invPixel(i, (sin(y * 6) * 20) + 23);
            myGLCD.update();
            __delay(11);
        }
    }
    __delay(1000 / FAST);
}


void Pacman() {

    for (int pc = 0; pc < 3; pc++)
    {
        pacy = random(0, 28);

        for (int i = -20; i<84; i++)
        {
            myGLCD.clrScr();
            for (int p = 4; p>((i + 20) / 20); p--)
                myGLCD.drawBitmap(p * 20 - 8, pacy + 7, pill, 5, 5);
            switch (((i + 20) / 3) % 4)
            {
            case 0: bm = pacman1;
                break;
            case 1: bm = pacman2;
                break;
            case 2: bm = pacman3;
                break;
            case 3: bm = pacman2;
                break;
            }
            myGLCD.drawBitmap(i, pacy, bm, 20, 20);
            myGLCD.update();
            __delay(25);
        }
    }
}


#define DEFAULT_WAIT 3000

void loop()
{

    digitalWrite(ON_BOARD_LED, HIGH);
    __delay(200);
    digitalWrite(ON_BOARD_LED, LOW);
    __delay(200);
    
    LogoMessage("Hello", "Sarah", "", DEFAULT_WAIT, 500);

    Transition1();
    DisplayImage(Graduating3, DEFAULT_WAIT);

    Transition2();
    DisplayImage(Sarah01, DEFAULT_WAIT);

    Transition3();
    DisplayImage(SarahTopModel, DEFAULT_WAIT);
    
    Transition4();
    DisplayImage(Ally, DEFAULT_WAIT);

    ScienceIsGreat();
    DisplayImage(Kelly_BW, DEFAULT_WAIT);

    LogoMessage("Good Luck", "At College.", "- Lea", DEFAULT_WAIT, 500);

    Transition1();
    DisplayImage(LEA_BW, DEFAULT_WAIT);

    Transition2();
    DisplayImage(AllySarahCamera, DEFAULT_WAIT);

    Transition3();
    DisplayImage(SarahLea, DEFAULT_WAIT);

    Transition4();
    DisplayImage(Anna2, DEFAULT_WAIT);

    LogoMessage("I love you", "Sasa.", "- Ally", DEFAULT_WAIT, 500);

    Transition1();
    DisplayImage(SarahAllyPool, DEFAULT_WAIT);

    Transition2();
    DisplayImage(Anna, DEFAULT_WAIT);

    Transition3();
    DisplayImage(Sarah10, DEFAULT_WAIT);

    Transition4();
    DisplayImage(SarahAllyLea, DEFAULT_WAIT);

    LogoMessage("You are po-po", "popular now.", "- Fred", DEFAULT_WAIT, 500);

    Transition1();
    DisplayImage(Graduating, DEFAULT_WAIT);

    Transition2();
    DisplayImage(Graduating2, DEFAULT_WAIT);

    Transition3();
    DisplayImage(Bryant, DEFAULT_WAIT);

    Transition4();
    DisplayImage(SarahLaughing, DEFAULT_WAIT);
    
    LogoMessage("Best wishes", "Karin.", "", DEFAULT_WAIT, 500);

    Transition1();
    DisplayImage(Sarah_WithHands, DEFAULT_WAIT);

    Transition2();
    DisplayImage(SarahOneMore, DEFAULT_WAIT);

    Transition3();
    DisplayImage(SarahJimmy, DEFAULT_WAIT);

    Transition4();
    ScienceIsGreatBackWard();

    Transition1();
    LogoMessage("Congrat!", "BC.", "- Emma.", DEFAULT_WAIT, 500);

    Transition2();
    LogoMessage("4th of July", "2015.", "", DEFAULT_WAIT, 500);
}
