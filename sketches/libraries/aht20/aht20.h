/*
  Interacts with AHT20 temperature & humidity sensor
*/

#ifndef aht20_h
#define aht20_h

#include "Arduino.h"

// Sensor i2c address
#define AHT20_I2C_ADDR 0x38

class AHT20 {
  private:
    static uint8_t STATUS_OK;
  public:
    AHT20();
    uint8_t begin();
    void getValues(float *temp, float *humid);
};

#endif