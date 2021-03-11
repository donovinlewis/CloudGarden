#include "comSMS.h"
#include "transceiver.h"

static soilMoist s;
static Transceiver radio;

void setup() {
    s.serialSoilInit();
}

void loop() {

  s.updateSoilSensing(SOILM);
  s.printSoilMoist();
  Transceiver::TransmittedData data{};
  data.currentMode = Transceiver::Mode::Default;
  data.batteryLevel = 100;
  data.temperature = 69;
  data.soilLevel = static_cast<uint16_t>(s.getSoilPct());
  int code = radio.Send(data);
  delay(1000);
}
