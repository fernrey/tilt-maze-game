#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <TinyScreen.h>

static unsigned long lastBlinkTime = 0;
static bool showPrompt = true;
static bool firstFrame = true;

// ---------------------------------------------------------
// HELPER: DRAW LETTERS (The "Code Font")
// ---------------------------------------------------------
// These functions draw 8-bit style letters using rectangles.
// Width: 12px, Height: 16px

void drawT(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 12, 4, TSRectangleFilled, c);      // Top Bar
  d.drawRect(x+4, y+4, 4, 12, TSRectangleFilled, c);  // Stem
}

void drawI(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 12, 4, TSRectangleFilled, c);      // Top Serif
  d.drawRect(x+4, y+4, 4, 8, TSRectangleFilled, c);   // Stem
  d.drawRect(x, y+12, 12, 4, TSRectangleFilled, c);   // Bot Serif
}

void drawL(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 4, 12, TSRectangleFilled, c);      // Stem
  d.drawRect(x, y+12, 12, 4, TSRectangleFilled, c);   // Bot Bar
}

void drawM(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 4, 16, TSRectangleFilled, c);      // Leg 1
  d.drawRect(x+8, y, 4, 16, TSRectangleFilled, c);    // Leg 2
  d.drawRect(x+4, y+4, 4, 4, TSRectangleFilled, c);   // V part
}

void drawA(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y+4, 4, 12, TSRectangleFilled, c);    // Leg 1
  d.drawRect(x+8, y+4, 4, 12, TSRectangleFilled, c);  // Leg 2
  d.drawRect(x+2, y, 8, 4, TSRectangleFilled, c);     // Top
  d.drawRect(x+2, y+8, 8, 4, TSRectangleFilled, c);   // Crossbar
}

void drawZ(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 12, 4, TSRectangleFilled, c);      // Top
  d.drawRect(x+6, y+4, 4, 4, TSRectangleFilled, c);   // Step 1
  d.drawRect(x+2, y+8, 4, 4, TSRectangleFilled, c);   // Step 2
  d.drawRect(x, y+12, 12, 4, TSRectangleFilled, c);   // Bot
}

void drawE(TinyScreen &d, int x, int y, uint8_t c) {
  d.drawRect(x, y, 4, 16, TSRectangleFilled, c);      // Spine
  d.drawRect(x+4, y, 8, 4, TSRectangleFilled, c);     // Top
  d.drawRect(x+4, y+6, 6, 4, TSRectangleFilled, c);   // Mid
  d.drawRect(x+4, y+12, 8, 4, TSRectangleFilled, c);  // Bot
}

//Draw Ball
void drawPixelBall(TinyScreen &d, int x, int y, uint8_t color) {
  d.drawRect(x+2, y, 4, 8, TSRectangleFilled, color);   // Vertical Core
  d.drawRect(x, y+2, 8, 4, TSRectangleFilled, color);   // Horizontal Core
  d.drawRect(x+1, y+1, 6, 6, TSRectangleFilled, color); // Filler
  
  // Add Shine (White pixel)
  d.drawRect(x+2, y+2, 2, 2, TSRectangleFilled, TS_8b_White);
}

// ---------------------------------------------------------
// MAIN DRAW FUNCTION
// ---------------------------------------------------------
void drawStartScreen(TinyScreen &display) {
  
  // 1. STATIC LAYER
  if (firstFrame) {
      // Background & Border
      display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Black); 
      display.drawRect(0, 0, 96, 64, TSRectangleNoFill, TS_8b_Green);
      display.drawRect(2, 2, 92, 60, TSRectangleNoFill, TS_8b_Green);

      //Starting position for TILT
      int startX = 20;
      int startY = 10;
      int space = 14; // Spacing between letters 
      
      // Shadows (Gray)
      drawT(display, startX+2, startY+2, TS_8b_Gray);
      drawI(display, startX+space+2, startY+2, TS_8b_Gray);
      drawL(display, startX+space*2+2, startY+2, TS_8b_Gray);
      drawT(display, startX+space*3+2 - 4, startY+2, TS_8b_Gray);
      
      // Make TILT font white
      drawT(display, startX, startY, TS_8b_White);
      drawI(display, startX+space, startY, TS_8b_White);
      drawL(display, startX+space*2, startY, TS_8b_White);
      drawT(display, startX+space*3 - 4, startY, TS_8b_White);

      // DRAW "MAZE"
      startX = 20; // Re-align
      startY = 28;
      
      // Shadows
      drawM(display, startX+2, startY+2, TS_8b_Gray);
      drawA(display, startX+space+2, startY+2, TS_8b_Gray);
      drawZ(display, startX+space*2+2, startY+2, TS_8b_Gray);
      drawE(display, startX+space*3+2, startY+2, TS_8b_Gray);
      
      // Main Text
      drawM(display, startX, startY, TS_8b_White);
      drawA(display, startX+space, startY, TS_8b_White);
      drawZ(display, startX+space*2, startY, TS_8b_White);
      drawE(display, startX+space*3, startY, TS_8b_White);

      drawPixelBall(display, 44, 46, TS_8b_Red);
      
      firstFrame = false; 
  }

  // 2. ANIMATION LAYER for blinking buttom
  if (millis() - lastBlinkTime > 500) { 
    lastBlinkTime = millis();
    showPrompt = !showPrompt; 
    
    // Button Location
    int btnX = 30;
    int btnY = 55;
    int btnW = 36;
    int btnH = 7;

    if (!showPrompt) {
       // Blink OFF: Cover with Black
       display.drawRect(btnX, btnY, btnW, btnH, TSRectangleFilled, TS_8b_Black);
    } else {
       // Blink ON: Yellow Button
       display.drawRect(btnX, btnY, btnW, btnH, TSRectangleFilled, TS_8b_Yellow);
       // Play Icon (Black Triangle)
       display.drawRect(btnX + 16, btnY + 1, 2, 5, TSRectangleFilled, TS_8b_Black);
       display.drawRect(btnX + 18, btnY + 2, 2, 3, TSRectangleFilled, TS_8b_Black);
    }
  }
}

#endif