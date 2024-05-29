/*
  Test how to work with SCD40 CO2 sensor.
  Use driver from https://github.com/Sensirion/arduino-i2c-scd4x/tree/master
*/

#include <Wire.h>
#include <SensirionI2CScd4x.h>

SensirionI2CScd4x scd4x;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  delay(6000);
  Serial.println("--SCD40 Tests--");
  scd4x.begin(Wire);
  scd4x.stopPeriodicMeasurement();

  scd4x.startPeriodicMeasurement();

  Serial.println("Waiting for first measurement... (5 sec)");
}
  /


void loop() {
  delay(1000);
  
  bool ready = false;
  scd4x.getDataReadyFlag(ready);

  if (ready){
    uint16_t co2;
    float temperature, humidity;

    scd4x.readMeasurement(co2, temperature, humidity);
    Serial.print("Co2:");
          Serial.print(co2);
          Serial.print("\t");
          Serial.print("Temperature:");
          Serial.print(temperature);
          Serial.print("\t");
          Serial.print("Humidity:");
          Serial.println(humidity);
  }
  else {
    Serial.println("Data not ready");
  }
}
