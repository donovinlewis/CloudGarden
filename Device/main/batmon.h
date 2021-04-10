#ifndef BATMON_H
#define BATMON_H

#include "Arduino.h"

class batmon {
public:
  uint32_t getVolts();

private:
  uint32_t battVolts{0};
  int getBG() {
    // Adust this value to your specific internal BG voltage x1000
    static constexpr long InternalReferenceVoltage = 1050L;
    // REFS1 REFS0          --> 0 1, AVcc internal ref.
    // MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)
    ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (1 << MUX3) |
            (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
    // Start a conversion
    ADCSRA |= _BV(ADSC);
    // Wait for it to complete
    while (((ADCSRA & (1 << ADSC)) != 0))
      ;
    // Scale the value
    int results = (((InternalReferenceVoltage * 1024L) / ADC) + 5L) / 10L;
    return results;
  }
};

#endif // BATMON_H defined, not batman unfortunately