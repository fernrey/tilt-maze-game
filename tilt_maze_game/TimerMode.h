#ifndef TIMERMODE_H
#define TIMERMODE_H

#include <Arduino.h>
#include "TinyScreen.h"
#include "MazeData.h"

extern TinyScreen display;

extern bool timerMode;
extern unsigned long levelStartTime;
extern unsigned long levelTimeLimit;
extern bool timeUp;
extern bool timeUpDrawn;
extern int lastDisplayedSeconds;

const unsigned long levelTimeLimits[] = {30000, 25000, 20000, 18000, 15000};

void startLevelTimer() {
  if (timerMode) {
    int level = currentLevel;
    if (level >= 5) level = 4;
    levelTimeLimit = levelTimeLimits[level];
    levelStartTime = millis();
    timeUp = false;
    timeUpDrawn = false;
    lastDisplayedSeconds = -1;
  }
}

unsigned long getRemainingTime() {
  if (!timerMode) return 0;
  unsigned long elapsed = millis() - levelStartTime;
  if (elapsed >= levelTimeLimit) return 0;
  return levelTimeLimit - elapsed;
}

void drawTimer() {
  if (!timerMode) return;
  
  unsigned long remaining = getRemainingTime();
  int seconds = remaining / 1000;
  
  if (seconds == lastDisplayedSeconds) return;
  lastDisplayedSeconds = seconds;
  
  display.setFont(liberationSansNarrow_8ptFontInfo);
  
  uint8_t timerColor;
  if (seconds > 10) {
    timerColor = TS_8b_Green;
  } else if (seconds > 5) {
    timerColor = TS_8b_Yellow;
  } else {
    timerColor = TS_8b_Red;
  }
  
  display.fontColor(timerColor, TS_8b_Black);
  display.setCursor(44, 1);
  
  if (seconds < 10) {
    display.print(" ");
  }
  display.print(seconds);
}

void showTimeUpScreen() {
  display.drawRect(20, 25, 56, 14, TSRectangleFilled, TS_8b_Red);
  display.setFont(liberationSansNarrow_8ptFontInfo);
  display.fontColor(TS_8b_White, TS_8b_Red);
  display.setCursor(24, 28);
  display.print("TIME UP!");
}

void adjustTimerForPause(unsigned long pausedTime) {
  if (timerMode) {
    unsigned long pauseDuration = millis() - pausedTime;
    levelStartTime += pauseDuration;
    lastDisplayedSeconds = -1;
  }
}

#endif