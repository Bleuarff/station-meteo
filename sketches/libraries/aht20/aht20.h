/*
  Interacts with AHT20 temperature & humidity sensor
*/

#ifndef aht20_h
#define aht20_h

#include "Arduino.h"

class AHT20 {
  private:
    static uint8_t I2C_ADDR;
    static uint8_t STATUS_OK;
  public:
    static uint8_t init();
    static void getValues(float *temp, float *humid);
};

#endif