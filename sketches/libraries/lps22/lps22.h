/*
  Interact with LPS22HB pressure sensor.
*/


#ifndef lps22hb_h
#define lps22hb_h

#include "Arduino.h"

#define LPS22HB_RES_CONF	0X1A //Normal (0) or Low current mode (1)
#define LPS22HB_CTRL_REG1	0X10 //output rate and filter settings
#define LPS22HB_CTRL_REG2	0X11 //BOOT FIFO_EN STOP_ON_FTH IF_ADD_INC I2C_DIS SWRESET One_Shot
#define LPS22HB_STATUS_REG	0X27 //Temp or Press data available bits
#define LPS22HB_PRES_OUT_XL	0X28 //XLSB
#define LPS22HB_PRES_OUT_L	0X29 //LSB
#define LPS22HB_PRES_OUT_H	0X2A //MSB
#define LPS22HB_TEMP_OUT_L	0X2B //LSB
#define LPS22HB_TEMP_OUT_H	0X2C //MSB

#define LPS22HB_I2C_ADDR 0x5D

class LPS22HB {
  private:
    uint8_t read(uint8_t reg);
    uint8_t write(uint8_t reg, uint8_t value);
    uint8_t status(uint8_t status);
  public:
    LPS22HB();
    uint8_t begin();
    void getValues(float *pressure, float *temperature);
};

#endif