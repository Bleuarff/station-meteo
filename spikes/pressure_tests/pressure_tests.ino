/*
  Test how to work with LPS22HB pressure sensor.
*/

#include <Wire.h>
#include <lps22hb.h>

LPS22HB lps22;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  delay(6000);
  Serial.println("--LPS22HB Tests--");

  lps22.begin();

  // set low power mode
  // Wire.beginTransmission(addr);
  // Wire.write(0x1A);
  // Wire.write(0x0);
  // Wire.endTransmission();

  // // set REG1 register with default values
  // Wire.beginTransmission(addr);
  // Wire.write(0x10);
  // Wire.write(0x0);
  // Wire.endTransmission();
}

// void showArray(byte arr[], int len) {
//   byte i;
//   for (i = 0; i < len; i++) {
//     Serial.printf(" %x", arr[i]);
//   }
//   Serial.print("  ");
// }

void loop() {

  // Serial.println("Run loop");
  float pressure, temp;
  lps22.getValues(&pressure, &temp);
  Serial.printf("P: %4.1f hPa\tT: %2.1f\n", pressure, temp);

  // // float p = readPressure();
  // // float t = readTemp();

  delay(4000);
}

// float readPressure() {
// 	// write(LPS22HB_CTRL_REG2, 0x1);

//   // configure one-shot mode
//   // Wire.beginTransmission(addr);
// 	// Wire.write(0x11);
// 	// Wire.write(0x1);
// 	// Wire.endTransmission();

// 	if (status(0x1) < 0)
// 		return 1.23;

//   // uint8_t buf[3];
//   // read(0x28, buf, 3);
//   // long val = ((long)buf[2] << 16) | ((long)buf[1] << 8) | (long)buf[0];
// 	uint8_t pressOutXL = read(0x28);
// 	uint8_t pressOutL = read(0x29);
// 	uint8_t pressOutH = read(0x2A);

// 	long val = ((long)pressOutH << 16) | ((long)pressOutL << 8) | (long)pressOutXL;
// 	//if (val == 1.00) readPressure();
// 	return val/4096.0f;
// }

// float readTemp(){
//   // trigger one-shot mode
//   Wire.beginTransmission(addr);
// 	Wire.write(0x11);
// 	Wire.write(0x1);
// 	Wire.endTransmission();

//   if (status(0x2) < 0)
// 		return 4.56;

//   // uint8_t buf[2] = {0, 0};
//   // read(0x2b, buf, 2);
//   // int16_t val = (buf[1] << 8) | (buf[0] & 0xff);

//   uint8_t tempOutH = read(0x2c);
// 	uint8_t tempOutL = read(0x2b);
// 	int16_t val = (tempOutH << 8) | (tempOutL & 0xff);

// 	return ((float)val)/100.0f;
// }

// void read(uint8_t reg, uint8_t buf[], uint8_t len){
//   Wire.beginTransmission(addr);
//   Wire.write(reg);
//   Wire.endTransmission();
//   Wire.requestFrom(addr, len);

//   uint8_t i = 0;
//   while(Wire.available()){
//     buf[i++] = Wire.read();
//   }
// }
