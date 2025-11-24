#ifndef BMA250_h
#define BMA250_h

#define BMA250_I2CADDR 0x18
#define BMA250_update_time_64ms 0x08
#define BMA250_update_time_32ms 0x09
// ... (all the other #defines are fine) ...
#define BMA250_range_2g 0x03
#define BMA250_range_4g 0x05
#define BMA250_range_8g 0x08
#define BMA250_range_16g 0x0C

#include <inttypes.h>
#include <Wire.h> // <-- ADD THIS

class BMA250 {
  public:
    BMA250();
    
    // --- THIS IS THE NEW BEGIN FUNCTION ---
    // It now accepts a pointer to the Wire library (e.g., &Wire1)
    void begin(TwoWire *wireBus, uint8_t range, uint8_t bw);
    
    // This is the old one, we'll leave it
    void begin(uint8_t, uint8_t);
    
    void read();
    int16_t X, Y, Z, rawTemp;

  // --- ADD THIS ---
  private:
    TwoWire *_wire; // Pointer to the I2C bus
};
#endif