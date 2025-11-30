#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "TinyScreen.h"

static unsigned long lastBlinkTime = 0;
static bool showPrompt = true;
static bool firstFrame = true;

// Mode selection
static int selectedMode = 0;
static bool modeSelected = false;

void drawT(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 12, 4, TSRectangleFilled, c);
  d.drawRect(x+4, y+4, 4, 12, TSRectangleFilled, c);
}

void drawI(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 12, 4, TSRectangleFilled, c);
  d.drawRect(x+4, y+4, 4, 8, TSRectangleFilled, c);
  d.drawRect(x, y+12, 12, 4, TSRectangleFilled, c);
}

void drawL(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 4, 12, TSRectangleFilled, c);
  d.drawRect(x, y+12, 12, 4, TSRectangleFilled, c);
}

void drawM(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 4, 16, TSRectangleFilled, c);
  d.drawRect(x+8, y, 4, 16, TSRectangleFilled, c);
  d.drawRect(x+4, y+4, 4, 4, TSRectangleFilled, c);
}

void drawA(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y+4, 4, 12, TSRectangleFilled, c);
  d.drawRect(x+8, y+4, 4, 12, TSRectangleFilled, c);
  d.drawRect(x+2, y, 8, 4, TSRectangleFilled, c);
  d.drawRect(x+2, y+8, 8, 4, TSRectangleFilled, c);
}

void drawZ(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 12, 4, TSRectangleFilled, c);
  d.drawRect(x+6, y+4, 4, 4, TSRectangleFilled, c);
  d.drawRect(x+2, y+8, 4, 4, TSRectangleFilled, c);
  d.drawRect(x, y+12, 12, 4, TSRectangleFilled, c);
}

void drawE(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 4, 16, TSRectangleFilled, c);
  d.drawRect(x+4, y, 8, 4, TSRectangleFilled, c);
  d.drawRect(x+4, y+6, 6, 4, TSRectangleFilled, c);
  d.drawRect(x+4, y+12, 8, 4, TSRectangleFilled, c);
}

void drawPixelBall(TinyScreen &d, int x, int y, uint8_t color) {
  d.drawRect(x+2, y, 4, 8, TSRectangleFilled, color);
  d.drawRect(x, y+2, 8, 4, TSRectangleFilled, color);
  d.drawRect(x+1, y+1, 6, 6, TSRectangleFilled, color);
  d.drawRect(x+2, y+2, 2, 2, TSRectangleFilled, TS_8b_White);
}

void drawModeSelect(TinyScreen &display) {
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Black);
  display.drawRect(0, 0, 96, 64, TSRectangleNoFill, TS_8b_Green);
  
  display.setFont(liberationSansNarrow_8ptFontInfo);
  display.fontColor(TS_8b_White, TS_8b_Black);
  display.setCursor(15, 5);
  display.print("SELECT MODE");
  
  uint8_t normalColor = (selectedMode == 0) ? TS_8b_Yellow : TS_8b_Gray;
  display.drawRect(10, 20, 76, 14, TSRectangleNoFill, normalColor);
  display.fontColor(normalColor, TS_8b_Black);
  display.setCursor(25, 23);
  display.print("NORMAL");
  
  uint8_t timerColor = (selectedMode == 1) ? TS_8b_Yellow : TS_8b_Gray;
  display.drawRect(10, 38, 76, 14, TSRectangleNoFill, timerColor);
  display.fontColor(timerColor, TS_8b_Black);
  display.setCursor(28, 41);
  display.print("TIMER");
  
  int arrowY = (selectedMode == 0) ? 24 : 42;
  display.fontColor(TS_8b_Yellow, TS_8b_Black);
  display.setCursor(3, arrowY);
  display.print(">");
}

void drawStartScreen(TinyScreen &display) {
  
  if (firstFrame) {
      display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Black); 
      display.drawRect(0, 0, 96, 64, TSRectangleNoFill, TS_8b_Green);
      display.drawRect(2, 2, 92, 60, TSRectangleNoFill, TS_8b_Green);

      int startX = 20;
      int startY = 10;
      int space = 14;
      
      drawT(display, startX+2, startY+2, TS_8b_Gray);
      drawI(display, startX+space+2, startY+2, TS_8b_Gray);
      drawL(display, startX+space*2+2, startY+2, TS_8b_Gray);
      drawT(display, startX+space*3+2 - 4, startY+2, TS_8b_Gray);
      
      drawT(display, startX, startY, TS_8b_White);
      drawI(display, startX+space, startY, TS_8b_White);
      drawL(display, startX+space*2, startY, TS_8b_White);
      drawT(display, startX+space*3 - 4, startY, TS_8b_White);

      startX = 20;
      startY = 28;
      
      drawM(display, startX+2, startY+2, TS_8b_Gray);
      drawA(display, startX+space+2, startY+2, TS_8b_Gray);
      drawZ(display, startX+space*2+2, startY+2, TS_8b_Gray);
      drawE(display, startX+space*3+2, startY+2, TS_8b_Gray);
      
      drawM(display, startX, startY, TS_8b_White);
      drawA(display, startX+space, startY, TS_8b_White);
      drawZ(display, startX+space*2, startY, TS_8b_White);
      drawE(display, startX+space*3, startY, TS_8b_White);

      drawPixelBall(display, 44, 46, TS_8b_Red);
      
      firstFrame = false; 
  }

  if (millis() - lastBlinkTime > 500) { 
    lastBlinkTime = millis();
    showPrompt = !showPrompt; 
    
    int btnX = 30;
    int btnY = 55;
    int btnW = 36;
    int btnH = 7;

    if (!showPrompt) {
       display.drawRect(btnX, btnY, btnW, btnH, TSRectangleFilled, TS_8b_Black);
    } else {
       display.drawRect(btnX, btnY, btnW, btnH, TSRectangleFilled, TS_8b_Yellow);
       display.drawRect(btnX + 16, btnY + 1, 2, 5, TSRectangleFilled, TS_8b_Black);
       display.drawRect(btnX + 18, btnY + 2, 2, 3, TSRectangleFilled, TS_8b_Black);
    }
  }
}

void resetStartScreen() {
  firstFrame = true;
  modeSelected = false;
  selectedMode = 0;
}

#endif