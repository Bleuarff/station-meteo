/*
  lps22.cpp - A library to interact with LPS22HB pressure sensor.
  Reference datasheet: https://www.mouser.fr/pdfdocs/enDM00140895.pdf
*/

#include "Arduino.h"
#include "Wire.h"
#include "lps22hb.h"

LPS22HB::LPS22HB(){
}

uint8_t LPS22HB::begin(){
  // set low power mode
  write(LPS22HB_RES_CONF, 0x0);

  // set REG1 register with default values
  write(LPS22HB_CTRL_REG1, 0x0);
  return 0;
}

// Get and return value of given register
uint8_t LPS22HB::read(uint8_t reg) {
	Wire.beginTransmission(LPS22HB_I2C_ADDR);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(LPS22HB_I2C_ADDR, 1);
	return Wire.read();
}

uint8_t LPS22HB::write(uint8_t reg, uint8_t value){
  Wire.beginTransmission(LPS22HB_I2C_ADDR);
	Wire.write(reg);
	Wire.write(value);
	return Wire.endTransmission();
}

uint8_t LPS22HB::status(uint8_t status) {
	int count = 1000;
	uint8_t data = 0xff;
	do {
		data = read(LPS22HB_STATUS_REG);
		--count;
		if (count < 0)
			break;
	} while ((data & status) == 0);

	if (count < 0)
		return -1;
	else
		return 0;
}

void LPS22HB::getValues(float *pressure, float *temperature){
  write(LPS22HB_CTRL_REG2, (uint8_t)1);

  if (status(0x1) < 0){
    *pressure = *temperature = -1.0f;
		return;
  }

  uint8_t pressOutXL = read(LPS22HB_PRES_OUT_XL);
	uint8_t pressOutL = read(LPS22HB_PRES_OUT_L);
	uint8_t pressOutH = read(LPS22HB_PRES_OUT_H);

	uint32_t pVal = ((long)pressOutH << 16) | ((long)pressOutL << 8) | (long)pressOutXL;
	*pressure = pVal/4096.0f;

  uint8_t tempOutH = read(LPS22HB_TEMP_OUT_H);
	uint8_t tempOutL = read(LPS22HB_TEMP_OUT_L);
	int16_t tVal = (tempOutH << 8) | (tempOutL & 0xff);

	*temperature = ((float)tVal)/100.0f;
}