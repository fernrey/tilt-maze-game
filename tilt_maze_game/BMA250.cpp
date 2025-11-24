#include "BMA250.h"
#include "Arduino.h"
#include <Wire.h>

BMA250::BMA250()
{
  // Default to the standard Wire bus
  _wire = &Wire;
}

// The new "begin" function that we will use
void BMA250::begin(TwoWire *wireBus, uint8_t range, uint8_t bw)
{
  // Save the bus we were given
  _wire = wireBus;
  
  // Now, use that bus for all commands
  _wire->beginTransmission(BMA250_I2CADDR);
  _wire->write(0x0F);
  _wire->write(range);
  _wire->endTransmission();
  
  _wire->beginTransmission(BMA250_I2CADDR);
  _wire->write(0x10);
  _wire->write(bw);
  _wire->endTransmission();
}

// The old "begin" function (we won't use this, but it's good to keep)
void BMA250::begin(uint8_t range, uint8_t bw)
{
  begin(&Wire, range, bw); // Just call the new one with the default
}


void BMA250::read()
{
  // Use the saved I2C bus
  _wire->beginTransmission(BMA250_I2CADDR);
  _wire->write(0x02);
  _wire->endTransmission();

  _wire->requestFrom(BMA250_I2CADDR, 7);
  
  X = (int16_t)_wire->read();
  X |= (int16_t)_wire->read() << 8;
  Y = (int16_t)_wire->read();
  Y |= (int16_t)_wire->read() << 8;
  Z = (int16_t)_wire->read();
  Z |= (int16_t)_wire->read() << 8;
  
  X >>= 6; Y >>= 6; Z >>= 6;
  
  rawTemp = _wire->read();
}