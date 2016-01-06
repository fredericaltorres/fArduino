/**************************************************************************

http://shop.evilmadscientist.com/productsmenu/tinykitlist/180-diavolino
ATmega328P
duemilanove

*************************************************************************/

#include "fArduino.h"

#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);

#define EX_LED1 2
Led _exLed1(EX_LED1);

#define EX_LED2 3
Led _exLed2(EX_LED2);



void setup() {

    Board.Delay(1500);
    Board.InitializeComputerCommunication(9600, "Initializing...");
    Board.TraceHeader("Diavolino = Duemilanove(ATmega328P)");
    
    Board.SetPinMode(ON_BOARD_LED, OUTPUT);
    _onBoardLed.SetBlinkMode(2000);

    Board.SetPinMode(EX_LED1, OUTPUT);
    _exLed1.SetBlinkMode(500);

    Board.SetPinMode(EX_LED2, OUTPUT);
    _exLed2.SetBlinkMode(500);
}

void loop() {

    _onBoardLed.Blink();
    _exLed1.Blink();
    _exLed2.Blink();
 
    Board.Delay(400);
}