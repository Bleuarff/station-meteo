/*
  Test cubecell low power modes
*/

uint8_t lowpower = 1;

static TimerEvent_t sleep;
static TimerEvent_t wakeup;

void onSleep(){
  Serial.println("Going to sleep");
  TimerSetValue(&wakeup, 10000);
  TimerStart(&wakeup);
  lowpower = 1;
}

void onWakeup(){
  lowpower = 0;
  digitalWrite(Vext, LOW);
  Serial.println("Waking up");
  Serial.println("Doing my things then sleeping again");
  delay(2000);
  onSleep();
  // TimerSetValue(&sleep, 5000);
  // TimerStart(&sleep);
}

void setup() {
  Serial.begin(115200);


  delay(6000);
  Serial.println("--Low power Tests--");
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, HIGH);

  TimerInit(&sleep, onSleep);
  TimerInit(&wakeup, onWakeup);
  onSleep();
}


void loop() {

 if (lowpower){
  digitalWrite(Vext, HIGH);
  lowPowerHandler();
 }
 else{
  // digitalWrite(Vext, LOW);
  Serial.println("Run...");
 }
}
