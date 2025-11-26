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
  // setting up the serial monitor for logging
  SerialMonitorInterface.begin(9600);

  // enabling the display and drawing a blank blue screen
  display.begin();
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
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
  y = (bma.X / 9) + 32;
  x = 48 - (bma.Y / 6);

  // printing the raw X & Y sensor values
  SerialMonitorInterface.print("X: ");
  SerialMonitorInterface.println(bma.X);
  SerialMonitorInterface.print("Y: ");
  SerialMonitorInterface.println(bma.Y);

  // stopping I2C communications
  Wire.end();

  // display uses these pins for SPI communications, specifically the chip select & data command lines
  // after we get our sensor reading, we want to set these back so that digitalRead/Write calls work for the display logic
  pinMode(0x16, OUTPUT); // DC (also used as SDA line for IC2 bus)
  pinMode(0x26, OUTPUT); // CS (also used as SCL line for IC2 bus)
}

void drawBall() {
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Blue);
  display.drawRect(x, y, 6, 6, TSRectangleFilled, TS_8b_Red);
}

