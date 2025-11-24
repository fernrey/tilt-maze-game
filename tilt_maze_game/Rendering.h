#ifndef RENDERING_H
#define RENDERING_H

#include <TinyScreen.h>
#include "MazeData.h"
#include "GameLogic.h"

extern TinyScreen display;

void drawMaze() {
  // Clear screen
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Black);

  // Draw walls with black borders (retro style)
  for (int y = 0; y < mazeHeight; y++) {
    for (int x = 0; x < mazeWidth; x++) {
      int pixelX = x * cellSize;
      int pixelY = y * cellSize;

      if (maze[y][x] == 1) {
        // Draw black border first (outer rectangle)
        display.drawRect(pixelX, pixelY, cellSize, cellSize, TSRectangleFilled, TS_8b_Black);

        // Draw white fill inside (inner rectangle, 1 pixel smaller on each side)
        display.drawRect(pixelX + 1, pixelY + 1, cellSize - 2, cellSize - 2, TSRectangleFilled, TS_8b_White);
      } else if (x == 22 && y == 14) {  // Your exit position
        // Draw exit with border too
        display.drawRect(pixelX, pixelY, cellSize, cellSize, TSRectangleFilled, TS_8b_Black);
        display.drawRect(pixelX + 1, pixelY + 1, cellSize - 2, cellSize - 2, TSRectangleFilled, TS_8b_Green);
      }
    }
  }
}

void updateBallPosition(int oldX, int oldY, int newX, int newY) {
  display.drawRect(oldX, oldY, ballSize, ballSize, TSRectangleFilled, TS_8b_Black);

  if (oldX >= goalX - ballSize && oldX <= goalX + cellSize && oldY >= goalY - ballSize && oldY <= goalY + cellSize) {
    display.drawRect(goalX, goalY, cellSize, cellSize, TSRectangleFilled, TS_8b_Green);
  }

  ballX = newX;
  ballY = newY;

  display.drawRect(ballX, ballY, ballSize, ballSize, TSRectangleFilled, TS_8b_Red);
}

void showLevelComplete() {
  int boxX = 18;
  int boxY = 20;
  int boxW = 60;
  int boxH = 24;

  display.drawRect(boxX, boxY, boxW, boxH, TSRectangleFilled, TS_8b_Black);
  display.drawRect(boxX, boxY, boxW, boxH, TSRectangleNoFill, TS_8b_White);

  display.setFont(liberationSansNarrow_8ptFontInfo);
  display.fontColor(TS_8b_Green, TS_8b_Black);
  display.setCursor(boxX + 12, boxY + 4);
  display.print("LEVEL 1");
  display.setCursor(boxX + 8, boxY + 14);
  display.print("FINISHED!");
}

void drawStartScreen() {
  // Clear screen
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Black);

  // Draw title
  display.setFont(liberationSansNarrow_8ptFontInfo);
  display.fontColor(TS_8b_White, TS_8b_Black);

  //Draw title of game
  display.setCursor(15, 15);
  display.print("TILT MAZE");

  // Draw "Press to Start"
  display.setCursor(10, 35);
  display.print("Press Start");

  // Draw a decorative border
  display.drawRect(5, 5, 86, 54, TSRectangleNoFill, TS_8b_White);
}
#endif