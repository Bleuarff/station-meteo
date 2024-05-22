/***************************************
 *
 * Ganymede: the outdoor module
 *      - temperature
 *      - humidity
 *      - atmospheric pressure
 *
 ***************************************/

// interval between loop checks
// actual production value: 5min (5 * 60 * 1000)
const unsigned long CLOCK_CHECK_INTERVAL = 4000;

// timestamp of last loop processing
unsigned long lastClockCheck = - CLOCK_CHECK_INTERVAL;

void setup(){
  Serial.begin(115200);
  delay(5000);
  Serial.println("** Ganymede starting **");
  lastClockCheck = millis();
}

void loop(){
  unsigned long ts = millis();
  unsigned long itv;

  if (ts >= lastClockCheck)
    itv = ts - lastClockCheck;
  else
    itv = UINT32_MAX - lastClockCheck + ts + 1;

  if (itv >= CLOCK_CHECK_INTERVAL){
    Serial.printf("Loop... %i\n", lastClockCheck);
    lastClockCheck = millis();
  }
}