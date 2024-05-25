/*
  aht20.cpp - Library to interact with AHT20 temperature & humidity sensor.
  Refer to https://asairsensors.com/wp-content/uploads/2021/09/Data-Sheet-AHT20-Humidity-and-Temperature-Sensor-ASAIR-V1.0.03.pdf
  for details.
*/

#include "Arduino.h"
#include "Wire.h"
#include "aht20.h"

uint8_t AHT20::I2C_ADDR = 0x38;
uint8_t AHT20::STATUS_OK = 0x18;

uint8_t AHT20::init(){
  // get sensor status
  Wire.beginTransmission(AHT20::I2C_ADDR);
  Wire.write(0x71);
  Wire.endTransmission();

  uint8_t c = Wire.requestFrom(AHT20::I2C_ADDR, (uint8_t)1);

  // unexpected bytes receive
  if (c != 1) {
    // Serial.printf("AHT returns %i bytes, expected 1.\n", c);
    return -1;
  }

  if (Wire.available() == 0) {
    // Serial.println("AHT is not available");
    return -2;
  }

  byte status = Wire.read();
  // Serial.printf("AHT status: %i\n", status);

  // Calibration required
  if (status != AHT20::STATUS_OK)
    return -3;

  delay(10);
  return 0;
}

// Get readings from sensor and convert to meaningful values
void AHT20::getValues(float *temp, float *humid){
  Wire.beginTransmission(AHT20::I2C_ADDR);
  byte cmd[3] = { 0xAC, 0x33, 0x00 };
  Wire.write(cmd, 3);
  Wire.endTransmission();

  // TODO: shorter wait time & retries
  delay(200);

  byte res[7];
  byte i = 0;
  Wire.requestFrom(AHT20::I2C_ADDR, (uint8_t)7);
  while (Wire.available()) {
    res[i++] = Wire.read();
  }

  long sh = (res[1] << 12) | (res[2] << 4) | (res[3] >> 4);
  *humid = (float)sh / 1048576 * 100;
  // // Serial.printf("Humidity: %2.1f%%\n", humid);

  byte msb = res[3]<<4; // take lower 4 bits, remove the humidity portion
  long th = (msb<<12) | (res[4]<<8) | res[5];
  *temp = (float)th / 1048576 * 200 - 50;
  // // Serial.printf("%d %d %d - %d - %d\n", res[3], res[4], res[5], msb, th);
  
  // Serial.printf("Temp: %2.1f°\tHumidity: %2.1f%%\n", temp);
}