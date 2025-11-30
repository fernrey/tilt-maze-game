#include "TinyScreen.h"
#include "TinyArcade.h"
#include "MazeData.h"
#include "GameLogic.h"
#include "Rendering.h"
#include "StartScreen.h"
#include "BMA250.h"
#include "Wireling.h"
#include <Wire.h>
#include "Music.h"
#include "TimerMode.h"
#include "Pause.h"

TinyScreen display = TinyScreen(TinyScreenPlus);
BMA250 bma;

// Screen states
bool showStartScreen = true;
bool showModeSelect = false;
bool modeSelectDrawn = false;
bool gameCompleteDrawn = false;
bool levelCompleteDrawn = false;

// Music variables
unsigned long lastNoteTime = 0;
int currentNote = 0;
int currentTrack = 0;
bool musicEnabled = true;

// Timer variables
bool timerMode = false;
unsigned long levelStartTime = 0;
unsigned long levelTimeLimit = 0;
bool timeUp = false;
bool timeUpDrawn = false;
int lastDisplayedSeconds = -1;

// Pause variables
bool paused = false;
bool pauseDrawn = false;
int pauseSelection = 0;
unsigned long pausedTime = 0;

// Accelerometer variables
int16_t accelX, accelY;
float ballVelX = 0;
float ballVelY = 0;

void exitPause() {
  paused = false;
  pauseDrawn = false;
  
  adjustTimerForPause(pausedTime);
  
  drawMaze();
  display.drawRect(ballX, ballY, ballSize, ballSize, TSRectangleFilled, TS_8b_Red);
}

void goToMenu() {
  paused = false;
  pauseDrawn = false;
  restartGame();
  gameComplete = false;
  gameCompleteDrawn = false;
  levelComplete = false;
  levelCompleteDrawn = false;
  timeUp = false;
  timeUpDrawn = false;
  resetStartScreen();
  showStartScreen = true;
  switchTrack(0);
}

void setup() {
  arcadeInit();
  display.begin();
  display.setBrightness(15);
  display.setFlip(false);
  
  pinMode(speakerPin, OUTPUT);
  
  loadLevel(0);
  switchTrack(0);
}

void loop() {
  if (showStartScreen) {
    drawStartScreen(display);
    updateMusic();
    
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      showStartScreen = false;
      showModeSelect = true;
      modeSelectDrawn = false;
      delay(200);
    }
    return;
  }
  
  if (showModeSelect) {
    if (!modeSelectDrawn) {
      drawModeSelect(display);
      modeSelectDrawn = true;
    }
    updateMusic();
    
    if (checkJoystick(TAJoystickUp) || checkJoystick(TAJoystickDown)) {
      selectedMode = (selectedMode == 0) ? 1 : 0;
      modeSelectDrawn = false;
      delay(200);
    }
    
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      timerMode = (selectedMode == 1);
      showModeSelect = false;
      modeSelectDrawn = false;
      modeSelected = true;


      //adding condition to only load levels if timer mode is selected.
      if(timerMode) {
        shuffleLevels();
      }
      else {
        levelsShuffled = false;
      }

      switchTrack(currentLevel + 1);
      resetGame();
      startLevelTimer();
      delay(200);
    }
    return;
  }
  
  if (paused) {
    if (!pauseDrawn) {
      drawPauseMenu();
      pauseDrawn = true;
    }
    
    if (checkJoystick(TAJoystickUp)) {
      pauseSelection--;
      if (pauseSelection < 0) pauseSelection = 2;
      pauseDrawn = false;
      delay(200);
    }
    
    if (checkJoystick(TAJoystickDown)) {
      pauseSelection++;
      if (pauseSelection > 2) pauseSelection = 0;
      pauseDrawn = false;
      delay(200);
    }
    
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      if (pauseSelection == 0) {
        exitPause();
      } else if (pauseSelection == 1) {
        musicEnabled = !musicEnabled;
        if (!musicEnabled) {
          stopMusic();
        }
        pauseDrawn = false;
      } else {
        goToMenu();
      }
      delay(200);
    }
    return;
  }
  
  if (timerMode && timeUp) {
    if (!timeUpDrawn) {
      showTimeUpScreen();
      timeUpDrawn = true;
    }
    
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      timeUpDrawn = false;
      resetGame();
      startLevelTimer();
      delay(200);
    }
    return;
  }
  
  if (gameComplete) {
    if (!gameCompleteDrawn) {
      showGameComplete();
      gameCompleteDrawn = true;
    }
    
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      restartGame();
      gameComplete = false;
      gameCompleteDrawn = false;
      resetStartScreen();
      showStartScreen = true;
      switchTrack(0);
      delay(200);
    }
    return;
  }
  
  if (levelComplete) {
    if (!levelCompleteDrawn) {
      showLevelComplete();
      levelCompleteDrawn = true;
    }
    
    if (checkButton(TAButton1) || checkButton(TAButton2)) {
      levelCompleteDrawn = false;
      nextLevel();
      switchTrack(currentLevel + 1);
      startLevelTimer();
      delay(200);
    }
    return;
  }
  
  if (checkButton(TAButton1)) {
    enterPause();
    delay(300);
    return;
  }
  
  if (timerMode && getRemainingTime() == 0) {
    timeUp = true;
    stopMusic();
    return;
  }
  
  drawTimer();
  updateMusic();
  
  int oldX = ballX;
  int oldY = ballY;
  int newX = ballX;
  int newY = ballY;
  
  readAccelerometer();
  
  ballVelX = ballVelX - accelX / 200.0;
  ballVelY = ballVelY + accelY / 200.0;
  
  ballVelX *= 0.95;
  ballVelY *= 0.95;
  
  newX = ballX + (int)ballVelX;
  newY = ballY + (int)ballVelY;

  if(checkCollision(newX, oldY)) {
    ballVelX = 0;
    newX = ballX;
  }
  if(checkCollision(newX, newY)) {
    ballVelY = 0;
    newY = ballY;
  }

  updateBallPosition(oldX, oldY, newX, newY);

  if (checkGoalReached()) {
      levelComplete = true;
      ballVelX = 0;
      ballVelY = 0;
  }
  
  delay(40);
}

void readAccelerometer() {
  Wireling.begin();
  bma.begin(BMA250_range_2g, BMA250_update_time_64ms);
  
  bma.read();
  accelY = bma.X;
  accelX = bma.Y;
  
  Wire.end();
  
  pinMode(0x16, OUTPUT);
  pinMode(0x26, OUTPUT);
}