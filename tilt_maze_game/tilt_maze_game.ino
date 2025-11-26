#include <TinyScreen.h>
#include "TinyArcade.h"
#include "MazeData.h"
#include "GameLogic.h"
#include "Rendering.h"
#include "StartScreen.h"

TinyScreen display = TinyScreen(TinyScreenPlus);

bool showStartScreen = true;  // Start with welcome screen

void setup() {
  arcadeInit();
  display.begin();
  display.setBrightness(15);
  display.setFlip(false);
  
  // Load the first level
  loadLevel(0);
  
}

void loop() {
  // Handle start screen
  if (showStartScreen) {
    
    drawStartScreen(display); 

    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      showStartScreen = false;
      resetGame(); 
      delay(200);  // Debounce
    }
    return; // Stop here, don't run game physics yet
  }

  // Handle game complete screen
  if (gameComplete) {
    showGameComplete();
    
    // Wait for button press to restart
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      restartGame();
      gameComplete = false;
      delay(200);  // Debounce
    }
    return;
  }

  // Handle level complete screen
  if (levelComplete) {
    showLevelComplete();
    
    // Wait for button press to go to next level
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      nextLevel();
      delay(200);  // Debounce
    }
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