#include "BMA250.h"
#include "Wireling.h"
#include "TinyScreen.h"
#include <Wire.h>

TinyScreen display = TinyScreen(TinyScreenPlus);
BMA250 bma; // Create an instance of the BMA250 object
int16_t x, y;

#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif

void setup() {
  SerialMonitorInterface.begin(9600);
  SerialMonitorInterface.print("hello");

  display.begin();
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
}

void loop() {
  readSensor();
  delay(16);
  drawBall();
  delay(16);
} 

void readSensor() {
  Wire.begin();
  Wireling.begin();
  bma.begin(BMA250_range_2g, BMA250_update_time_32ms);
  bma.read();
  x = 32 - (bma.X / 9);
  y = (bma.Y / 6) + 48;
    SerialMonitorInterface.print("X: ");
  SerialMonitorInterface.println(bma.X);
  SerialMonitorInterface.print("Y: ");
  SerialMonitorInterface.println(bma.Y);
  Wire.end();
  pinMode(0x16, OUTPUT);
  pinMode(0x26, OUTPUT);
}

void drawBall() {
  //display.reset();
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
  display.drawRect(y, x, 6, 6, TSRectangleFilled, TS_8b_Red);
}

