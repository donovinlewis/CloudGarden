// Common libraries needed across sections
#include "Arduino.h"
#include <LowPower.h>

// Custom Libraries
#include "sms.h"
#include "batmon.h"
#include "thermo.h"
#include "transceiver.h"

static constexpr int SUCCESS{0};

using Calibration = soilMoist::Calibration;
using Mode = Transceiver::Mode;

// objects representing device connections
static soilMoist s;
static Transceiver radio;
static thermistor thermo;
static batmon batman;

// static variables
static Mode currentMode{Mode::Default};

void setup() {
  // Serial.begin(115200);
  s.serialSoilInit();
  radio.Initialize();
  thermo.init();
}

void loop() {
  digitalWrite(s.OUTPUT_PIN, HIGH);
  digitalWrite(thermo.OUTPUT_PIN, HIGH);
  delay(100);

  // read soil moisture
  uint16_t soilPct = ReadSoilMoisture();
  int16_t tempF = ReadTemperature();
  uint16_t volts = ReadVoltage();
  int success = Transmit(currentMode, soilPct, tempF, volts);
  success |= Receive(currentMode);
  //   if (success != SUCCESS) {
  //     currentMode = Transceiver::Mode::Default;
  //   }

  // TODO: add calibration
  // Calibration cal = ???;
  // Calibrate(cal);
  Sleep(currentMode);
}

// helper functions
uint16_t ReadSoilMoisture() {
  s.updateSoilSensing();
  return static_cast<uint16_t>(s.getSoilPct());
}

int16_t ReadTemperature() {
  float tempF = thermo.getTemperature();
  return static_cast<int16_t>(tempF);
}

uint16_t ReadVoltage() {
  uint32_t volts = batman.getVolts();
  return static_cast<uint16_t>(volts);
}

void Calibrate(const Calibration cal) {
  int val = s.getSoilVal();
  if (cal == Calibration::Air) {
    s.setAirVal(val);
  } else if (cal == Calibration::Water) {
    s.setWatVal(val);
  }
}

int Transmit(Mode currentMode, uint16_t soilLevel, int16_t temperature,
             uint16_t batteryLevel) {
  Transceiver::TransmittedData data{};
  data.currentMode = static_cast<uint8_t>(currentMode);
  data.soilLevel = soilLevel;
  data.temperature = temperature;
  data.batteryLevel = batteryLevel;
  return radio.Send(data);
}

int Receive(Mode &newMode) {
  Transceiver::ReceivedData data{};
  int code = radio.Receive(data);
  newMode = data.mode;
  return code;
}

void Sleep(Mode currentMode) {
  static constexpr uint16_t HOUR_IN_SECONDS{3600};
  static constexpr uint16_t RAPID_SLEEP_TIME{5};
  uint16_t sleepTimeSeconds{HOUR_IN_SECONDS};
  switch (currentMode) {
  case Mode::Calibration:
    sleepTimeSeconds = RAPID_SLEEP_TIME;
    break;
  case Mode::Off:
    sleepTimeSeconds = 0;
    break;
  default:
    break;
  }
  // put the radio to sleep
  radio.Sleep();
  // Note: this function wakes up every 8 seconds
  // using the arduino watch dog timer.
  // a better solution may need to be implemented
  return LowPower.longPowerDown(sleepTimeSeconds * 1000);
}
