#include "thermo.h"

float thermistor::getTemperature() const {
  const int V0{analogRead(INPUT_PIN)};
  static constexpr float A{1.009249522e-03};
  static constexpr float B{2.378405444e-04};
  static constexpr float C{2.019202697e-07};
  const float logRT = log(10000 * ((1024 / V0) - 1));
  const float T = (1 / (A + B * logRT + C * logRT * logRT * logRT));
  const float TC = T - 273.15;
  const float TF = (TC * 1.8) + 32;
  return TF;
}