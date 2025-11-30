#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "TinyScreen.h"
#include "MazeData.h"

extern TinyScreen display;

// Game state variables
int ballX = 2;
int ballY = 2;
const int ballSize = 3;
bool levelComplete = false;
bool gameComplete = false;  // NEW: Track if all levels are finished

// Check if position collides with walls
bool checkCollision(int newX, int newY) {
  // Check all four corners of the ball
  int corners[4][2] = {
    {newX, newY},
    {newX + ballSize - 1, newY},
    {newX, newY + ballSize - 1},
    {newX + ballSize - 1, newY + ballSize - 1}
  };
  
  for (int i = 0; i < 4; i++) {
    int gridX = corners[i][0] / cellSize;
    int gridY = corners[i][1] / cellSize;
    
    // Check screen boundaries
    if (corners[i][0] < 0 || corners[i][0] >= 96 || 
        corners[i][1] < 0 || corners[i][1] >= 64) {
      return true;
    }
    
    // Check grid boundaries
    if (gridX < 0 || gridX >= mazeWidth || gridY < 0 || gridY >= mazeHeight) {
      return true;
    }
    
    // Check if hitting a wall
    if (maze[gridY][gridX] == 1) {
      return true;
    }
  }
  
  return false;
}

// Check if ball reached the goal
bool checkGoalReached() {
  int ballGridX = (ballX + ballSize/2) / cellSize;
  int ballGridY = (ballY + ballSize/2) / cellSize;
  
  return (ballGridX == goalPositions[currentMazeIndex][0] && ballGridY == goalPositions[currentMazeIndex][1]);
}

// Forward declarations
void drawMaze();
void showLevelComplete();
void showGameComplete();

// Reset game to initial state
void resetGame() {
  ballX = cellSize + 1;
  ballY = cellSize + 1;
  levelComplete = false;
  
  display.clearScreen(); //this line here clears the display before the maze is drawn. Preventing menu and maze overlap.
  drawMaze();
  
  display.drawRect(ballX, ballY, ballSize, ballSize, TSRectangleFilled, TS_8b_Red);
}

// Load next level
void nextLevel() {
  if (currentLevel < totalLevels - 1) {
    // Load next level
    loadLevel(currentLevel + 1);
    resetGame();
    levelComplete = false;
  } else {
    // All levels complete!
    gameComplete = true;
  }
}

// Restart from level 1
void restartGame() {
  loadLevel(0);  // Load level 1
  resetGame();
  levelComplete = false;
  gameComplete = false;
}

#endif