#ifndef RENDERING_H
#define RENDERING_H

#include <TinyScreen.h>
#include "MazeData.h"
#include "GameLogic.h"

extern TinyScreen display;

// Draw the entire maze
void drawMaze() {
  // Clear screen
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Black);
  
  // Draw walls and exit
  for (int y = 0; y < mazeHeight; y++) {
    for (int x = 0; x < mazeWidth; x++) {
      if (maze[y][x] == 1) {
        display.drawRect(x * cellSize, y * cellSize, cellSize, cellSize, 
                         TSRectangleFilled, TS_8b_White);
      } else if (x == 22 && y == 14) {
        display.drawRect(x * cellSize, y * cellSize, cellSize, cellSize, 
                         TSRectangleFilled, TS_8b_Green);
      }
    }
  }
}

// Update ball position on screen
void updateBallPosition(int oldX, int oldY, int newX, int newY) {
  // Erase old position
  display.drawRect(oldX, oldY, ballSize, ballSize, TSRectangleFilled, TS_8b_Black);
  
  // Redraw goal if ball was over it
  if (oldX >= goalX - ballSize && oldX <= goalX + cellSize &&
      oldY >= goalY - ballSize && oldY <= goalY + cellSize) {
    display.drawRect(goalX, goalY, cellSize, cellSize, TSRectangleFilled, TS_8b_Green);
  }
  
  // Update position
  ballX = newX;
  ballY = newY;
  
  // Draw ball at new position
  display.drawRect(ballX, ballY, ballSize, ballSize, TSRectangleFilled, TS_8b_Red);
}

// Show level complete message
void showLevelComplete() {
  int boxX = 18;
  int boxY = 20;
  int boxW = 60;
  int boxH = 24;
  
  // Draw popup box
  display.drawRect(boxX, boxY, boxW, boxH, TSRectangleFilled, TS_8b_Black);
  display.drawRect(boxX, boxY, boxW, boxH, TSRectangleNoFill, TS_8b_White);
  
  // Display text
  display.setFont(liberationSansNarrow_8ptFontInfo);
  display.fontColor(TS_8b_Green, TS_8b_Black);
  display.setCursor(boxX + 12, boxY + 4);
  display.print("LEVEL 1");
  display.setCursor(boxX + 8, boxY + 14);
  display.print("FINISHED!");
}

#endif