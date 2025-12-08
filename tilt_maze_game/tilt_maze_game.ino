#include "BMA250.h"
#include "Wireling.h"
#include "TinyScreen.h"
#include <Wire.h>

TinyScreen display = TinyScreen(TinyScreenPlus);
BMA250 bma; // create an instance of the BMA250 (accelerometer) object
int16_t x, y; // variables holding the x & y acceleration values

// variables for the ball's current position within the screen, defaulting to its center
int currBallPosX = 48; 
int currBallPosY = 32;

// variables for the ball's current velocity vector, defaulting to 0 (standstill)
float ballVelX = 0;
float ballVelY = 0;

#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif

void setup() {
  // setting up the serial monitor for logging
  SerialMonitorInterface.begin(9600);

  // enabling the display and drawing a blank blue screen
  display.begin();
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
  display.drawRect(currBallPosX, currBallPosY, 3, 3, TSRectangleFilled, TS_8b_Red);
  display.setFont({
  10, /*  Character height */
  ' ', /*  Start character */
  '~', /*  End character */
  thinPixel7_10ptDescriptors, /*  Character descriptor array */
  thinPixel7_10ptBitmaps, /*  Character bitmap array */
}); 
}

void loop() {
  readSensor();
  // adding some delay between sensor and display calls, may not be necessary
  delay(32);
  drawBall();
  // adding some more delay in between the calls, totaling to the sensor's update rate
  delay(32);
} 

void readSensor() {
  // setting up I2C communications, 
  // which hijacks the shared SDA & SCL processor pins normally used by the display
  Wireling.begin();
  bma.begin(BMA250_range_2g, BMA250_update_time_64ms);
  // requesting the sensor data and mapping it to 'global' variables
  bma.read();
  y = bma.X;
  x = bma.Y;

  // stopping I2C communications
  Wire.end();

  // display uses these pins for SPI communications, specifically the chip select & data command lines
  // after we get our sensor reading, we want to set these back so that digitalRead/Write calls work for the display logic
  pinMode(0x16, OUTPUT); // DC (also used as SDA line for IC2 bus)
  pinMode(0x26, OUTPUT); // CS (also used as SCL line for IC2 bus)
}

void drawBall() {
  // updating the current velocity of the ball
  // using the acceleration values provided by the sensor
  ballVelX = ballVelX - x/200.0;
  ballVelY = ballVelY + y/200.0;

  // logging velocity values
  SerialMonitorInterface.print("X Velocity: ");
  SerialMonitorInterface.print(ballVelX);
  SerialMonitorInterface.print(" Y Velocity: ");
  SerialMonitorInterface.println(ballVelY);

  // calculating the new X & Y positions
  int newBallPosX = currBallPosX + ballVelX;
  int newBallPosY = currBallPosY + ballVelY;

  // collision check with the borders of the screen

  // if the ball's expected position hits a border:
  // reset its velocity to 0 and position the ball at the border
  if(newBallPosX <= display.xMax && newBallPosX >= 0){
    currBallPosX = newBallPosX;
  } else {
    currBallPosX = newBallPosX < 0 ? 0 : display.xMax;
    ballVelX = 0;
  }
  if(newBallPosY <= display.yMax && newBallPosY >= 0){
    currBallPosY = newBallPosY;
  } else {
    currBallPosY = newBallPosY < 0 ? 0 : display.yMax;
    ballVelY = 0;
  }

  // finally, draw the ball at its new position
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
  display.drawRect(currBallPosX, currBallPosY, 3, 3, TSRectangleFilled, TS_8b_Red);
  display.setCursor(0, 0);
  display.print("posX:");
  display.print(currBallPosX);
  display.print(" Y:");
  display.print(currBallPosY);
  display.setCursor(0, 10);
  display.print("velX:");
  display.print(ballVelX, 1);
  display.print(" Y:");
  display.print(ballVelY, 1);
  display.setCursor(0, 20);
  display.print("accelX:");
  display.print(x/200.0, 1);
  display.print(" Y:");
  display.print(y/200.0, 1);
}

