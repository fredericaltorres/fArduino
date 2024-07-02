#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "TFT_eSPI.h"
#include "ScreenManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// ScreenManager
/////

ScreenManager::ScreenManager(TFT_eSprite * sprite) {

   this->_pin = 0;
   this->_sprite = sprite;
}
ScreenManager::~ScreenManager() {
}

#define gray 0x6B6D
#define blue 0x0967
#define orange 0xC260
#define purple 0x604D
#define green 0x1AE9
#define SCREEN_MANAGER_MAX_X 320
#define SCREEN_MANAGER_MAX_Y 170
#define SCREEN_MANAGER_FONT_TITLE_INDEX 2
#define SCREEN_MANAGER_FONT_TEXT_INDEX 2
#define SCREEN_MANAGER_TITLE_HEIGHT 19
#define SCREEN_MANAGER_CONSOLE_MODE_MAX_LINE 8

// https://github.com/Bodmer/TFT_eSPI/blob/master/TFT_eSPI.h

void ScreenManager::DrawStatus(String title, bool error /*= false*/) {

   Serial.println(title);

   if(error)
       this->_sprite->setTextColor(TFT_RED, blue);
   else
       this->_sprite->setTextColor(TFT_YELLOW, blue);

   this->_sprite->fillRoundRect(1, SCREEN_MANAGER_MAX_Y- SCREEN_MANAGER_TITLE_HEIGHT-1, SCREEN_MANAGER_MAX_X - 1, SCREEN_MANAGER_MAX_Y , 1, blue);

   this->_sprite->setTextDatum(TC_DATUM); // Centre text on x,y position
   int xpos = this->_sprite->width() / 2; // Half the screen width

   this->_sprite->drawString(title, xpos, SCREEN_MANAGER_MAX_Y - SCREEN_MANAGER_TITLE_HEIGHT, SCREEN_MANAGER_FONT_TITLE_INDEX);
   this->_sprite->pushSprite(0, 0);
}

void ScreenManager::DrawWindow(String title) {

   Serial.println(title);

   this->_sprite->fillSprite(TFT_BLACK);
   this->_sprite->setTextColor(TFT_WHITE, blue);

   this->_sprite->drawRect(0, 0, SCREEN_MANAGER_MAX_X-1, SCREEN_MANAGER_MAX_Y-1, blue);
   this->_sprite->drawRect(1, 1, SCREEN_MANAGER_MAX_X-2, SCREEN_MANAGER_MAX_Y-2, blue);

   this->_sprite->fillRoundRect(1, 1, SCREEN_MANAGER_MAX_X - 1, SCREEN_MANAGER_TITLE_HEIGHT, 1, blue);

   this->_sprite->setTextDatum(TC_DATUM); // Centre text on x,y position
   int xpos = this->_sprite->width() / 2; // Half the screen width

   this->_sprite->drawString(title, xpos, 2, SCREEN_MANAGER_FONT_TITLE_INDEX);
   this->_sprite->pushSprite(0, 0);
}

void ScreenManager::Clear() {

   this->_sprite->fillRoundRect(1, SCREEN_MANAGER_TITLE_HEIGHT, SCREEN_MANAGER_MAX_X - 3, SCREEN_MANAGER_MAX_Y - 10, 1, TFT_BLACK);

   // Bug re-draw bottom border
   this->_sprite->drawRect(0, 0, SCREEN_MANAGER_MAX_X - 1, SCREEN_MANAGER_MAX_Y - 1, blue);
   this->_sprite->drawRect(1, 1, SCREEN_MANAGER_MAX_X - 2, SCREEN_MANAGER_MAX_Y - 2, blue);

   this->_currentY = ScreenManager_CURRENT_Y_START;
   this->_lineCounter = 0;
}

void ScreenManager::DrawText(String text) {

   Serial.println(text);
   this->_sprite->setTextColor(TFT_WHITE, TFT_BLACK);
   this->_sprite->setTextDatum(TL_DATUM);
   int xpos = 10;
   this->_sprite->drawString(text, xpos, this->_currentY, SCREEN_MANAGER_FONT_TEXT_INDEX);
   this->_sprite->pushSprite(0, 0);
   this->_currentY += ScreenManager_CURRENT_Y_INCR;
   this->_lineCounter += 1;
   if (this->_lineCounter == SCREEN_MANAGER_CONSOLE_MODE_MAX_LINE) {
       this->Clear();
   }
}

void ScreenManager::Init() {

   this->_sprite->createSprite(SCREEN_MANAGER_MAX_X, SCREEN_MANAGER_MAX_Y);
   this->_sprite->setTextDatum(3);
   this->_sprite->setSwapBytes(true);
}
