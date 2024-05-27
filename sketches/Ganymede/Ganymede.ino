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
#include <lps22hb.h>

// interval between loop checks
// actual production value: 5min (5 * 60 * 1000)
const unsigned long CLOCK_CHECK_INTERVAL = 4000;


// timestamp of last loop processing
unsigned long lastClockCheck = -CLOCK_CHECK_INTERVAL;

AHT20 aht20;
LPS22HB lps22;

float temp, humid, pressure, temp2;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(2000);
  Serial.println("** Ganymede starting **");

  aht20.begin();
  lps22.begin();
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

    // TODO:
    //  - get all sensor values
    //  - send them to base station
    //  - sleep

    if (aht20.isReady) {
      // Retrieve value from temp & humidity sensors
      aht20.getValues(&temp, &humid);
    }

    lps22.getValues(&pressure, &temp2);

    Serial.printf("T: %2.1f°\tH: %2.1f%%\tP: %4.1fhPa\tT2: %2.1f°\n", temp, humid, pressure, temp2);
    lastClockCheck = millis();
  }
}
