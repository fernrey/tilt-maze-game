/*************************************************************************
 * Accelerometer BMA250 Wireling Tutorial:
 * This example program will show the basic method of printing out the 
 * accelerometer values from the BMA250 to the Serial Monitor/Serial Plotter
 * 
 * Hardware by: TinyCircuits
 * Code by: Laveréna Wienclaw for TinyCircuits
 *
 * Initiated: 11/29/2017 
 * Updated: 12/06/2019
 ************************************************************************/
 
#include <Wire.h>         // For I2C communication with sensor
#include <Wireling.h>     // For interfacing with Wirelings
#include "BMA250.h"       // For interfacing with the accel. sensor
#include <TinyScreen.h>

// Accelerometer sensor variables for the sensor and its values
BMA250 accel_sensor;
int x, y, z, temp;
TinyScreen display = TinyScreen(TinyScreenPlus);
int drawBallX, drawBallY;

// Make Serial Monitor compatible for all TinyCircuits processors
#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif

void setup() {
  SerialMonitorInterface.begin(115200);
  Wire.begin();

  display.begin();
  display.setBrightness(15);
  display.setFlip(false);
  display.drawRect(0, 0, 96, 64, TSRectangleFilled, TS_8b_Red);
  display.drawRect(20, 20, 4, 4, TSRectangleFilled, TS_8b_Yellow);


  // Initialize Wireling
  Wireling.begin();
  Wireling.selectPort(0); 

  // Sets up the BMA250 accelerometer
  accel_sensor.begin(BMA250_range_2g, BMA250_update_time_64ms); 
}

void loop() {
  accel_sensor.read();//This function gets new data from the accelerometer

  // Get the acceleration values from the sensor and store them into local variables
  // (Makes reading the rest of the program easier)
  x = accel_sensor.X;
  y = accel_sensor.Y;
  z = accel_sensor.Z;
  drawBallX = (y / 6) + 48;
  drawBallY = (x / 9) + 32;
  temp = ((accel_sensor.rawTemp * 0.5) + 24.0, 1);

 // If the BMA250 is not found, nor connected correctly, these values will be produced
 // by the sensor 
  if (x == -1 && y == -1 && z == -1) {
    // Print error message to Serial Monitor
    SerialMonitorInterface.print("ERROR! NO BMA250 DETECTED!");
  }
  else { // if we have correct sensor readings: 
    display.drawRect(drawBallX, drawBallY, 4, 4, TSRectangleFilled, TS_8b_Yellow);
    showSerial();                 //Print to Serial Monitor or Serial Plotter
  }

  
  


  // The BMA250 can only poll new sensor values every 64ms, so this delay
  // will ensure that we can continue to read values
  delay(256);
  // ***Without the delay, there would not be any sensor output*** 
}

// Prints the sensor values to the Serial Monitor (found under 'Tools')
void showSerial() {
  SerialMonitorInterface.print("X = ");
  SerialMonitorInterface.print(x);
  
  SerialMonitorInterface.print("  Y = ");
  SerialMonitorInterface.print(y);
  
  SerialMonitorInterface.print("  Z = ");
  SerialMonitorInterface.print(z);
  
  SerialMonitorInterface.print("  Temperature(C) = ");
  SerialMonitorInterface.println((accel_sensor.rawTemp * 0.5) + 24.0, 1);

  SerialMonitorInterface.print("X-position to render ball = ");
  SerialMonitorInterface.println(drawBallX);
  SerialMonitorInterface.print("Y-position to render ball = ");
  SerialMonitorInterface.println(drawBallY);
}