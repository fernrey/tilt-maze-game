#include "BMA250.h"
#include "Wireling.h"
#include "TinyScreen.h"

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


  Wireling.begin();
  bma.begin(BMA250_range_2g, BMA250_update_time_64ms);
}

void loop() {
  drawBall();
  delay(32);
  readSensor();
  delay(32);
} 

void readSensor() {
  Wireling.begin();
  bma.begin(BMA250_range_2g, BMA250_update_time_64ms);
  bma.read();
  x = 32 - (bma.X / 9);
  y = (bma.Y / 6) + 48;
    SerialMonitorInterface.print("X: ");
  SerialMonitorInterface.println(bma.X);
  SerialMonitorInterface.print("Y: ");
  SerialMonitorInterface.println(bma.Y);
}

void drawBall() {
  display.reset();
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
  display.drawRect(y, x, 6, 6, TSRectangleFilled, TS_8b_Red);
}

