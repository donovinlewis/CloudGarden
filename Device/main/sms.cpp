#include "sms.h"

void soilMoist::updateSoilSensing() {
  soilVal = analogRead(INPUT_PIN);
  soilPct = map(soilVal, airVal, watVal, 0, 100);
}

void soilMoist::setWatVal(const int val) { watVal = val; }

void soilMoist::setAirVal(const int val) { airVal = val; }

int soilMoist::getSoilPct() const { return soilPct; }

int soilMoist::getSoilVal() const { return soilVal; }

void soilMoist::serialSoilInit() {
  if (Serial) {
    Serial.println(" Time (s) , Analog Reading , Percent Value ");
  }
  init();
}

void soilMoist::printSoilMoist() const {
  const long curSec = millis() / 1000;
  Serial.print(curSec, HEX);

  Serial.print(" , ");
  Serial.print(soilVal, HEX);

  Serial.print(" , ");
  Serial.println(soilPct, HEX);
}
