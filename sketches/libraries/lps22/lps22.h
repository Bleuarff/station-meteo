/*
  Interact with LPS22HB pressure sensor.
*/


#ifndef lp22_h
#define lps22_h

#include "Arduino.h"

class LPS22 {
  private:
    static uint8_t I2C_ADDR;
  // public:
  //   static uint8_t init();
  //   static void getValues(float *temp, float *humid);
};

#endif