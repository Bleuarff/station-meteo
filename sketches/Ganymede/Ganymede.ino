/***************************************
 *
 * Ganymede: the outdoor module
 *      - temperature
 *      - humidity
 *      - atmospheric pressure
 *
 ***************************************/

#include <Wire.h>
#include <aht20.h>

// interval between loop checks
// actual production value: 5min (5 * 60 * 1000)
const unsigned long CLOCK_CHECK_INTERVAL = 4000;


// timestamp of last loop processing
unsigned long lastClockCheck = -CLOCK_CHECK_INTERVAL;

bool AHTReady = false;
float temp, humid;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(5000);
  Serial.println("** Ganymede starting **");
  lastClockCheck = millis();

  uint8_t error = AHT20::init();
  AHTReady = (error == 0);
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
      // Retrieve value from temp & humidity sensors
      AHT20::getValues(&temp, &humid);
      Serial.printf("T: %2.1f°\tH: %2.1f%%\n", temp, humid);
    }

    lastClockCheck = millis();
  }
}
