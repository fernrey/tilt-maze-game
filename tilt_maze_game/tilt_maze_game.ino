#include <TinyScreen.h>
#include "TinyArcade.h"
#include "MazeData.h"
#include "GameLogic.h"
#include "Rendering.h"

TinyScreen display = TinyScreen(TinyScreenPlus);

bool showStartScreen = true;  // Start with welcome screen

void setup() {
  arcadeInit();
  display.begin();
  display.setBrightness(15);
  display.setFlip(false);
  
  drawStartScreen();
}

void loop() {

   if (showStartScreen) {
    if (checkButton(TAButton1) || checkButton(TAButton2) || 
        checkJoystick(TAJoystickUp) || checkJoystick(TAJoystickDown) ||
        checkJoystick(TAJoystickLeft) || checkJoystick(TAJoystickRight)) {
      showStartScreen = false;
      resetGame();  // Start the game
      delay(200);  // Debounce
    }
    return;
  }

  // Check for restart
  if (checkButton(TAButton1) || checkButton(TAButton2)) {
    resetGame();
    delay(200);
    return;
  }
  
  // If level complete, show message
  if (levelComplete) {
    showLevelComplete();
    delay(100);
    return;
  }
  
  // Store old position
  int oldX = ballX;
  int oldY = ballY;
  int newX = ballX;
  int newY = ballY;
  
  // Read D-pad input
  if (checkJoystick(TAJoystickUp))    newY -= 1;
  if (checkJoystick(TAJoystickDown))  newY += 1;
  if (checkJoystick(TAJoystickLeft))  newX -= 1;
  if (checkJoystick(TAJoystickRight)) newX += 1;

  // Only move if no collision
  if (!checkCollision(newX, newY)) {
    updateBallPosition(oldX, oldY, newX, newY);
    
    // Check win condition
    if (checkGoalReached()) {
      levelComplete = true;
    }
  }
  
  delay(40);
}