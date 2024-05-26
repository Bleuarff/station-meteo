/*
  Test how to work with LPS22HB pressure sensor.
*/

#include <Wire.h>
// #include <lps22.h>

uint8_t addr = 0x5D;

void setup(){
  Serial.begin(115200);
  Wire.begin();

  delay(4000);
  Serial.println("--LPS22HB Tests--");

  // set low power mode
  Wire.beginTransmission(addr);
	Wire.write(0x1A);
	Wire.write(0x0);
	Wire.endTransmission();

  // set REG1 register with default values
  Wire.beginTransmission(addr);
	Wire.write(0x10);
	Wire.write(0x0);
	Wire.endTransmission();
}

void showArray(byte arr[], int len){
  byte i;
  for (i = 0; i < len; i++){
    Serial.printf(" %x", arr[i]);
  }
  Serial.print("  ");
}

void loop(){
  

  float p = readPressure();
  float t = readTemp();
  Serial.printf("P: %4.1f hPa\tT: %2.1f\n", p, t);

  delay(4000);
}

float readPressure() {
	// write(LPS22HB_CTRL_REG2, 0x1);

  // configure one-shot mode
  Wire.beginTransmission(addr);
	Wire.write(0x11);
	Wire.write(0x1);
	Wire.endTransmission();

	if (status(0x1) < 0)
		return 1.23;
	//delay(50);
	uint8_t pressOutXL = read(0x28);
	uint8_t pressOutL = read(0x29);
	uint8_t pressOutH = read(0x2A);

	long val = ((long)pressOutH << 16) | ((long)pressOutL << 8) | (long)pressOutXL;
	//if (val == 1.00) readPressure();
	return val/4096.0f;
}

float readTemp(){
  // configure one-shot mode
  Wire.beginTransmission(addr);
	Wire.write(0x11);
	Wire.write(0x1);
	Wire.endTransmission();

  if (status(0x2) < 0)
		return 4.56;

  uint8_t tempOutH = read(0x2c);
	uint8_t tempOutL = read(0x2b);

	int16_t val = (tempOutH << 8) | (tempOutL & 0xff);
	return ((float)val)/100.0f;
}

uint8_t read(uint8_t reg) {
	Wire.beginTransmission(addr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(addr, (byte)1);
	return Wire.read();
}

uint8_t status(uint8_t status) {
	int count = 1000;
	uint8_t data = 0xff;
	do {
		data = read(0x27);
		--count;
		if (count < 0)
			break;
	} while ((data & status) == 0);

	if (count < 0)
		return -1;
	else
		return 0;
}