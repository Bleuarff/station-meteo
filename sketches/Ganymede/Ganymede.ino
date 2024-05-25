/***************************************
 *
 * Ganymede: the outdoor module
 *      - temperature
 *      - humidity
 *      - atmospheric pressure
 *
 ***************************************/

// #include <Adafruit_AHTX0.h>
#include <Wire.h>

// interval between loop checks
// actual production value: 5min (5 * 60 * 1000)
const unsigned long CLOCK_CHECK_INTERVAL = 4000;

const uint8_t AHT20_ADDRESS = 0x38;

// timestamp of last loop processing
unsigned long lastClockCheck = -CLOCK_CHECK_INTERVAL;

bool AHTReady = false;
// Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(5000);
  Serial.println("** Ganymede starting **");
  lastClockCheck = millis();

  initAHT();
}

void loop() {
  unsigned long ts = millis();
  unsigned long itv;

  // compute interval since last check
  if (ts >= lastClockCheck)
    itv = ts - lastClockCheck;
  else
    // rollover occurred, compute interval accordingly
    itv = UINT32_MAX - lastClockCheck + ts + 1;

  // do its job only if interval is sufficient
  if (itv >= CLOCK_CHECK_INTERVAL) {
    // Serial.printf("Loop... %i\n", lastClockCheck);

    // TODO:
    //  - get all sensor values
    //  - send them to base station
    //  - sleep

    if (AHTReady) {
      getAHTValues();
    }

    lastClockCheck = millis();
  }
}

// https://asairsensors.com/wp-content/uploads/2021/09/Data-Sheet-AHT20-Humidity-and-Temperature-Sensor-ASAIR-V1.0.03.pdf
void initAHT() {
  Serial.println("Sensor init...");

  // get sensor status
  Wire.beginTransmission(AHT20_ADDRESS);
  Wire.write(0x71);
  Wire.endTransmission();

  uint8_t c = Wire.requestFrom(AHT20_ADDRESS, (uint8_t)1);

  if (c != 1) {
    Serial.printf("AHT returns %i bytes, expected 1.\n", c);
    return;
  }

  if (Wire.available() == 0) {
    Serial.println("AHT is not available");
    return;
  }

  byte status = Wire.read();
  Serial.printf("AHT status: %i\n", status);

  if (status != 0x18)
    Serial.print("AHT status is invalid, initialization process is required");
  else {
    AHTReady = true;
    delay(10);
  }
}

// Retrieve value from temp & humidity sensors
void getAHTValues() {
  Wire.beginTransmission(AHT20_ADDRESS);
  byte cmd[3] = { 0xAC, 0x33, 0x00 };
  Wire.write(cmd, 3);
  Wire.endTransmission();
  // TODO: shorter wait time & retries
  delay(200);

  byte res[7];
  byte i = 0;
  Wire.requestFrom(AHT20_ADDRESS, (uint8_t)7);
  while (Wire.available()) {
    res[i++] = Wire.read();
  }

  long sh = (res[1] << 12) | (res[2] << 4) | (res[3] >> 4);
  float humid = (float)sh / 1048576 * 100;
  // Serial.printf("Humidity: %2.1f%%\n", humid);

  byte msb = res[3]<<4;
  long th = (msb<<12) | (res[4]<<8) | res[5];
  float temp = (float)th / 1048576 * 200 - 50;
  // Serial.printf("%d %d %d - %d - %d\n", res[3], res[4], res[5], msb, th);
  
  Serial.printf("Temp: %2.1f°\tHumidity: %2.1f%%\n", temp);
}