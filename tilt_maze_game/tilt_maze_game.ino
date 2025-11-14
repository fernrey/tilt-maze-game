#include <TinyScreen.h>
#include "TinyArcade.h"

TinyScreen display = TinyScreen(TinyScreenPlus);

int ballX = 45;
int ballY = 30;

void setup() {
  arcadeInit();  // MUST call this first to setup joystick
  display.begin();
  display.setBrightness(15);
  display.setFlip(false);
  
  // Draw blue background
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
}

void loop() {
  // Erase old ball (draw blue over it)
  display.drawRect(ballX, ballY, 6, 6, TSRectangleFilled, TS_8b_Blue);
  
  // Check each direction and move ball
  if (checkJoystick(TAJoystickUp)) {
    ballY -= 2;  // Move up
  }
  if (checkJoystick(TAJoystickDown)) {
    ballY += 2;  // Move down
  }
  if (checkJoystick(TAJoystickLeft)) {
    ballX -= 2;  // Move left
  }
  if (checkJoystick(TAJoystickRight)) {
    ballX += 2;  // Move right
  }

  // Keep ball on screen (boundary checks)
  if (ballX < 0) ballX = 0;           // Left edge
  if (ballX > 90) ballX = 90;         // Right edge (96 - 6 = 90)
  if (ballY < 0) ballY = 0;           // Top edge
  if (ballY > 58) ballY = 58;         // Bottom edge (64 - 6 = 58)

  
  // Draw ball at new position (red square)
  display.drawRect(ballX, ballY, 6, 6, TSRectangleFilled, TS_8b_Red);
  
  delay(50);
}