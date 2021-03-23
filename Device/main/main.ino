#include "comSMS.h"

static constexpr int SUCCESS{0};

static soilMoist s;
static Transceiver radio;
static uint8_t currentMode;

using Mode = Transceiver::Mode;

void setup() { s.serialSoilInit(); }

void loop() {

  // read soil moisture
  uint16_t soilPct = ReadSoilMoisture();
  // uint16_t temperature = getTemperature(); // TODO: add temperature function
  // uint16_t batteryLevel = getBatteryLevel(); // TODO: add battery monitoring
  int success = Transmit(currentMode, soilPct, 69, 100);
  success |= Receive(currentMode);
  if (success != SUCCESS) {
    currentMode = Transceiver::Mode::Default;
  }
  Sleep(currentMode);
}

// helper functions
uint16_t ReadSoilMoisture() {
	s.updateSoilSensing(PINS::SOILM);
	return static_cast<uint16_t>(s.getSoilPct());
}

int Transmit(Mode currentMode, uint16_t soilLevel, uint16_t temperature,
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
	}
	radio.Sleep();
	// Note: this function wakes up every 8 seconds
	// using the arduino watch dog timer.
	// a better solution may need to be implemented
	return LowPower.longPowerDown(sleepTimeSeconds * 1000);
}