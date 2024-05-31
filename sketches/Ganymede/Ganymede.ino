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
const unsigned long SLEEP_INTERVAL = 10000;

uint8_t lowpowermode = 0;

static TimerEvent_t wakeup;

AHT20 aht20;
LPS22HB lps22;

float temp, humid, pressure, temp2;

void setup() {
  Serial.begin(115200);
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);  // power i2c sensors
  Wire.begin();

  delay(2000);
  Serial.println("** Ganymede starting **");

  TimerInit(&wakeup, onWakeup);
}

// Prepare for sleep: close i2c bus, pull Vext OFF
void onSleep() {
  Wire.end();
  delay(100);
  digitalWrite(Vext, HIGH);
  TimerSetValue(&wakeup, SLEEP_INTERVAL);
  TimerStart(&wakeup);
  lowpowermode = 1;
}

// wake up: pull Vext ON and start i2c bus
void onWakeup() {
  digitalWrite(Vext, LOW);
  Wire.begin();
  lowpowermode = 0;
  delay(500);
}

void loop() {
  if (lowpowermode){
    // put cpu in deep sleep
    lowPowerHandler();
  }
  else {
    // take a measure before going back to sleep
    takeMeasure();
    delay(100);
    onSleep();
  }
}

void takeMeasure() {
  aht20.begin();
  lps22.begin();

  if (aht20.isReady) {
    // Retrieve value from temp & humidity sensors
    aht20.getValues(&temp, &humid);
  }

  lps22.getValues(&pressure, &temp2);
  Serial.printf("T: %2.1f°\tH: %2.1f%%\tP: %4.1fhPa\tT2: %2.1f°\n", temp, humid, pressure, temp2);
}