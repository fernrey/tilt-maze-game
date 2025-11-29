#ifndef PAUSE_H
#define PAUSE_H

#include <Arduino.h>
#include "TinyScreen.h"
#include "Music.h"

extern TinyScreen display;
extern bool musicEnabled;

extern bool paused;
extern bool pauseDrawn;
extern int pauseSelection;
extern unsigned long pausedTime;

void drawPauseMenu() {
  display.drawRect(15, 12, 66, 44, TSRectangleFilled, TS_8b_Black);
  display.drawRect(15, 12, 66, 44, TSRectangleNoFill, TS_8b_Yellow);
  
  display.setFont(liberationSansNarrow_8ptFontInfo);
  display.fontColor(TS_8b_Yellow, TS_8b_Black);
  display.setCursor(30, 14);
  display.print("PAUSED");
  
  uint8_t resumeColor = (pauseSelection == 0) ? TS_8b_Yellow : TS_8b_Gray;
  display.fontColor(resumeColor, TS_8b_Black);
  display.setCursor(32, 25);
  display.print("RESUME");
  
  uint8_t musicColor = (pauseSelection == 1) ? TS_8b_Yellow : TS_8b_Gray;
  display.fontColor(musicColor, TS_8b_Black);
  display.setCursor(26, 35);
  display.print("MUSIC:");
  display.print(musicEnabled ? "ON" : "OFF");
  
  uint8_t menuColor = (pauseSelection == 2) ? TS_8b_Yellow : TS_8b_Gray;
  display.fontColor(menuColor, TS_8b_Black);
  display.setCursor(38, 45);
  display.print("MENU");
  
  int arrowY;
  if (pauseSelection == 0) arrowY = 25;
  else if (pauseSelection == 1) arrowY = 35;
  else arrowY = 45;
  
  display.fontColor(TS_8b_Yellow, TS_8b_Black);
  display.setCursor(18, arrowY);
  display.print(">");
}

void enterPause() {
  paused = true;
  pauseDrawn = false;
  pauseSelection = 0;
  stopMusic();
  pausedTime = millis();
}

#endif