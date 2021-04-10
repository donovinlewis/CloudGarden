#include "batmon.h"

uint32_t batmon::getVolts() {
  for (int i = 0; i <= 2; i++)
  {
      battVolts += getBG();
  }
  battVolts = battVolts / 3;
  return battVolts;
}