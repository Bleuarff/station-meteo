/*
  lps22.cpp - A library to interact with LPS22HB pressure sensor.
  Reference datasheet: https://www.mouser.fr/pdfdocs/enDM00140895.pdf
*/

#include "Arduino.h"
#include "Wire.h"
#include "lps22.h"

uint8_t LPS22::I2C_ADDR = 0x5C;
