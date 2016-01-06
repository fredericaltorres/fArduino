//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//
///// The class drive an LCD via an I2C chip PCF8574
///// Where to buy:
/////     http://www.aliexpress.com/snapshot/6653662565.html?orderId=67164328734214
///// Detail Information about the LCD + I2C and I2C
/////     https://www.youtube.com/watch?v=KTDw3Z_amiU
///// Arduino Reference
/////     http://playground.arduino.cc/Code/LCDi2c
//
//LiquidCrystal_I2C lcd(0x27, 16, 4);  // set the LCD address to 0x20 for a 16 chars and 2 line display
//
//void setup()
//{
//    lcd.init();                      // initialize the lcd 
//
//    lcd.clear();
//    delay(1000);
//    lcd.setCursor(0, 0);
//    delay(1000);
//    // Print a message to the LCD.
//    
//    lcd.print("Hello, world!");
//    delay(1000);
//}
//
//void loop()
//{
//    lcd.setCursor(0, 0);
//    delay(1000);
//    lcd.backlight();
//}


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {

    lcd.init();
    lcd.cursor_on();
    lcd.blink_on();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello, world !");
    lcd.setCursor(4, 2);
    lcd.print("Pobot is alive !");
    delay(1000);
    lcd.cursor_off();
    lcd.blink_off();
}

void loop() {
}