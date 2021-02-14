#ifndef SMS_H
#define SMS_H

#include "Arduino.h"

class soilMoist{
private:
    int soilVal, soilPct, airVal, watVal;
    unsigned long curSec;


public:
    soilMoist();
    void updateSoilSensing(const int analogPin);

    void setAirVal(const int analogPin);
    void setWatVal(const int analogPin);

    int getSoilPct();
    int getSoilVal();

    void serialSoilInit();
    void printSoilMoist();

};

#endif
