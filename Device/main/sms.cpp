#include "sms.h"


soilMoist::soilMoist(){
    airVal = 565;
    watVal = 293;
}

void soilMoist::updateSoilSensing(const int analogPin){
    soilVal = analogRead(analogPin); 
    soilPct = map(soilVal, airVal, watVal, 0, 100);
}

void soilMoist::setWatVal(const int analogPin){
    watVal = analogRead(analogPin);
}

void soilMoist::setAirVal(const int analogPin){
    airVal = analogRead(analogPin);
}

int soilMoist::getSoilPct(){
    return soilPct;
}

int soilMoist::getSoilVal(){
    return soilVal;
}

void soilMoist::serialSoilInit(){
    Serial.println(" Time (s) , Analog Reading , Percent Value ");
}

void soilMoist::printSoilMoist(){
    curSec = millis()/1000;
    Serial.print(curSec, HEX);

    Serial.print(" , ");
    Serial.print(soilVal, HEX);

    Serial.print(" , ");
    Serial.println(soilPct, HEX);
}
