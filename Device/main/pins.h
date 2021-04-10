#ifndef PINS_H
#define PINS_H

#include "Arduino.h"

struct pins {
  pins(uint8_t input, uint8_t output) : INPUT_PIN{input}, OUTPUT_PIN{output} {}
  void init() {
    pinMode(INPUT_PIN, INPUT);
    pinMode(OUTPUT_PIN, OUTPUT);
  }
  uint8_t INPUT_PIN;
  uint8_t OUTPUT_PIN;
};

#endif // PINS_H defined