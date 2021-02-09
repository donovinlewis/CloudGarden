#include "sms.h"

int soilVal, soilPct;
unsigned long curSec;

int airVal, watVal;


void updateSoilSensing(){
    soilVal = analogRead(A0); 
    soilPct = map(soilVal, airVal, watVal, 0, 100);
}

void setWatVal(){
    watVal = analogRead(A0);
}

void setAirVal(){
    airVal = analogRead(A0);
}

void getSoilPct(int& soilO){
    soilO = soilPct;
}

void getSoilVal(int& soilO){
    soilO = soilVal;
}