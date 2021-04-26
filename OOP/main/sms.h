#ifndef SMS_H
#define SMS_H

#include "pins.h"

class soilMoist : public pins {
private:
  int soilVal, soilPct, airVal, watVal;

public:
  soilMoist() : pins{PC0, PD5}, airVal{565}, watVal{293} {};

  void updateSoilSensing();

  void setAirVal(const int val);
  void setWatVal(const int val);

  int getSoilPct() const;
  int getSoilVal() const;

  void serialSoilInit();
  void printSoilMoist() const;

  enum Calibration : uint8_t { None = 0, Air = 1, Water = 2 };
};

#endif
