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

}


void loop() {

  // Serial.println("Run loop");
  float pressure, temp;
  lps22.getValues(&pressure, &temp);
  Serial.printf("P: %4.1f hPa\tT: %2.1f\n", pressure, temp);

  delay(4000);
}
