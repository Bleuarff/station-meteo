/*
  lps22.cpp - A library to interact with LPS22HB pressure sensor.
  Reference datasheet: https://www.mouser.fr/pdfdocs/enDM00140895.pdf
*/

#include "Arduino.h"
#include "Wire.h"
#include "lps22hb.h"

LPS22HB::LPS22HB(){
}


// Write control register to ensure correct configuration
uint8_t LPS22HB::begin(){
  // set low power mode
  write(LPS22HB_RES_CONF, 0x0);
  write(LPS22HB_CTRL_REG1, 0x0);
  return 0;
}

// Get and return value of given register
uint8_t LPS22HB::read(uint8_t reg) {
	uint8_t buf[1];
	read(reg, buf, 1);
	return buf[0];
}

void LPS22HB::read(uint8_t reg, uint8_t buf[], uint8_t len){
  Wire.beginTransmission(LPS22HB_I2C_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(LPS22HB_I2C_ADDR, (int)len);

  uint8_t i = 0;
  while(Wire.available()){
    buf[i++] = Wire.read();
  }
}

// Write value at register reg
uint8_t LPS22HB::write(uint8_t reg, uint8_t value){
  Wire.beginTransmission(LPS22HB_I2C_ADDR);
	Wire.write(reg);
	Wire.write(value);
	return Wire.endTransmission();
}

// check status register for data availability
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

// get pressure and temperature readings
void LPS22HB::getValues(float *pressure, float *temperature){
	// Trigger one-shot value, with register auto-increment to read all bytes at once.
  write(LPS22HB_CTRL_REG2, 0b10001);

  if (status(0b11) < 0){
    *pressure = *temperature = -1.0f;
		return;
  }

	uint8_t buf[5];
	read(LPS22HB_PRES_OUT_XL, buf, 5);
  uint8_t pressOutXL = buf[0];
	uint8_t pressOutL = buf[1];
	uint8_t pressOutH = buf[2];
	uint32_t pVal = ((long)pressOutH << 16) | ((long)pressOutL << 8) | (long)pressOutXL;
	*pressure = pVal/4096.0f;

  uint8_t tempOutL = buf[3];
	uint8_t tempOutH = buf[4];
	int16_t tVal = (tempOutH << 8) | (tempOutL & 0xff);

	*temperature = ((float)tVal)/100.0f;
}