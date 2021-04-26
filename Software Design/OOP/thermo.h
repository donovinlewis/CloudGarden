#ifndef THERMO_H
#define THERMO_H

#include "pins.h"

class thermistor : public pins {
public:
  thermistor() : pins{PC1, PD4} {}
  float getTemperature() const;
};

#endif // THERMO_H defined