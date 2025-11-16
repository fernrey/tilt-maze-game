#include <TinyScreen.h>
#include "TinyArcade.h"
#include "MazeData.h"
#include "GameLogic.h"
#include "Rendering.h"

TinyScreen display = TinyScreen(TinyScreenPlus);

void setup() {
  arcadeInit();  // MUST call this first to setup joystick
  display.begin();
  display.setBrightness(15);
  display.setFlip(false);
  
  resetGame();
}

void loop() {
  // Check for restart button (Button 1 or Button 2)
  if (checkButton(TAButton1) || checkButton(TAButton2)) {
    resetGame();
    delay(200);  // Debounce delay
    return;
  }
  
  // If level is complete, show the message
  if (levelComplete) {
    showLevelComplete();
    delay(100);
    return;
  }
  
  int oldX = ballX;
  int oldY = ballY;
  int newX = ballX;
  int newY = ballY;
  
  // Check each direction and calculate new position
  if (checkJoystick(TAJoystickUp)) {
    newY -= 1;  // Slower movement for precision
  }
  if (checkJoystick(TAJoystickDown)) {
    newY += 1;
  }
  if (checkJoystick(TAJoystickLeft)) {
    newX -= 1;
  }
  if (checkJoystick(TAJoystickRight)) {
    newX += 1;
  }

  // Only move if no collision
  if (!checkCollision(newX, newY)) {
    // Erase old ball position
    updateBallPosition(oldX, oldY, newX, newY);
    
    // Update position
    ballX = newX;
    ballY = newY;
    
    // Check if we reached the goal
    if (checkGoalReached()) {
      levelComplete = true;
    }
  }
  
  delay(40);  // Slightly faster refresh for smoother movement
}