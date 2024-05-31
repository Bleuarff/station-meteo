/*
  aht20.cpp - Library to interact with AHT20 temperature & humidity sensor.
  Refer to https://asairsensors.com/wp-content/uploads/2021/09/Data-Sheet-AHT20-Humidity-and-Temperature-Sensor-ASAIR-V1.0.03.pdf
  for details.
*/

#include "Arduino.h"
#include "Wire.h"
#include "aht20.h"

AHT20::AHT20(){ }

void AHT20::begin(){
  isReady = false;
  delay(100); // wait >= 100ms after power-on

  uint8_t c = 0;
  int i = 0;
  long start = millis();
  do{
    // get sensor status
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x71);
    Wire.endTransmission();

    c = Wire.requestFrom(I2C_ADDR, (uint8_t)1);
  
    if (c != 1)
      delay(100);
  }
  while (c != 1 && i++ < 100);

  long duration = millis() - start;
  // unexpected bytes receive
  if (c != 1) {
    Serial.printf("AHT returns %i bytes, expected 1. [%ims]\n", c, duration);
    return;
  }
  Serial.printf("AHT20 ready [%dms]\n", duration);

  if (Wire.available() == 0) {
    Serial.println("AHT is not available");
    return;
  }

  uint8_t status = Wire.read();

  // Calibration required
  if (status != AHT20::STATUS_OK){
    Serial.printf("AHT20 status: %i\n", status);
    return;
  }

  isReady = true;
  delay(10); // delay after init, before sending a read command
}

// Get readings from sensor and compute values
void AHT20::getValues(float *temp, float *humid){

  // measurement trigger command + 2 bytes of parameters
  uint8_t cmd[3] = { 0xAC, 0x33, 0x00 };

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(cmd, 3);
  Wire.endTransmission();

  bool ready = false;
  do {
    delay(85); // delay > 80ms recommended

    // get sensor status
    Wire.requestFrom(I2C_ADDR, (uint8_t)1);

    if (Wire.available()) {
      uint8_t status = Wire.read();
      ready = status < 128; // bit[7] at 0 means device is ready.
    }
    else
      Serial.println("Read error");
  } while (!ready);

  uint8_t res[7];
  uint8_t i = 0;
  Wire.requestFrom(I2C_ADDR, (uint8_t)7);

  while (Wire.available()) {
    res[i++] = Wire.read();
  }

  // Compute values from bytes 1-5. First byte is status, last one is CRC (ignored).

  // merge bytes to obtain a 20-bit value
  long sh = (res[1] << 12) | (res[2] << 4) | (res[3] >> 4);
  *humid = (float)sh / 1048576 * 100; // formula according to datasheet

  // merge to 20-bit value
  uint8_t msb = res[3]<<4; // take lower 4 bits, remove the humidity portion
  long th = (msb<<12) | (res[4]<<8) | res[5];
  *temp = (float)th / 1048576 * 200 - 50; // formula according to datasheet
}