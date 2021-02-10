#ifndef SMS_H
#define SMS_H

#include "Arduino.h"

void updateSoilSensing(const int analogPin);

void setAirVal(const int analogPin);
void setWatVal(const int analogPin);

void getSoilPct(int& soilO);
void getSoilVal(int& soilO);

void serialSoilInit();
void printSoilMoist();

#endif
