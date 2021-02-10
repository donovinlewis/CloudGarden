#include "sms.h"

int soilVal, soilPct;
unsigned long curSec;

int airVal, watVal;


void updateSoilSensing(const int analogPin){
    soilVal = analogRead(analogPin); 
    soilPct = map(soilVal, airVal, watVal, 0, 100);
}

void setWatVal(const int analogPin){
    watVal = analogRead(analogPin);
}

void setAirVal(const int analogPin){
    airVal = analogRead(analogPin);
}

void getSoilPct(int& soilO){
    soilO = soilPct;
}

void getSoilVal(int& soilO){
    soilO = soilVal;
}