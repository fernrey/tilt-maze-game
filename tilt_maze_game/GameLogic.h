#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <TinyScreen.h>  // ADD THIS
#include "MazeData.h"

extern TinyScreen display;  // ADD THIS

// Game state variables
int ballX = 2;
int ballY = 2;
const int ballSize = 3;
bool levelComplete = false;

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
  
  return (ballGridX == 22 && ballGridY == 14);
}

// Forward declaration
void drawMaze();  // ADD THIS

// Reset game to initial state
void resetGame() {
  ballX = cellSize + 1;  // Start at (9, 9) approximately
  ballY = cellSize + 1;
  levelComplete = false;
  
  drawMaze();
  
  display.drawRect(ballX, ballY, ballSize, ballSize, TSRectangleFilled, TS_8b_Red);
}

#endif