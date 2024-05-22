
// interval between loop checks
const unsigned long CLOCK_CHECK_INTERVAL = 4000;

// timestamp of last we checked the time
unsigned long lastClockCheck;

void setup(){
  Serial.begin(115200);
  delay(5000);
  Serial.println("Setup OK");
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