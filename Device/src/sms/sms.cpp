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

void serialSoilInit(){
    Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
    Serial.println(" Time (s) , Analog Reading , Percent Value ");
}

void printSoilMoist(){
    unsigned long curSeconds = millis()/1000;
    Serial.print(curSeconds);

    Serial.print(" , ");
    Serial.print(soilVal);

    Serial.print(" , ");
    Serial.println(soilPct);
}