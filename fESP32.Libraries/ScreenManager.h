// SCREEN_MANAGER.h

#ifndef _SCREEN_MANAGER_h
#define _SCREEN_MANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define ScreenManager_CURRENT_Y_START 23
#define ScreenManager_CURRENT_Y_INCR 16

class ScreenManager {

private:
   int _pin;
   TFT_eSprite *_sprite;
   int _currentY = ScreenManager_CURRENT_Y_START;
   int _lineCounter = 0;

public:
   ScreenManager(TFT_eSprite *sprite);
   ~ScreenManager();
   void Init();
   void DrawWindow(String title);
   void DrawStatus(String title, bool error = false);
   void DrawText(String text);
   void Clear();
};
#endif