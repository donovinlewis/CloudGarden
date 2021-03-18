#ifndef TRANSCEIVER_HPP
#define TRANSCEIVER_HPP
// includes from LowPowerLab library
#include <LowPower.h>
#include <RFM69.h>

// standard library includes.
#include <stdint.h>

// helper functions
static constexpr uint8_t MSByte(uint16_t i) {
  return static_cast<uint8_t>(i & 0xFF00);
}

static constexpr uint8_t LSByte(uint16_t i) {
  return static_cast<uint8_t>(i & 0x00FF);
}

class Transceiver : private RFM69 {
public:
  // constructor
  Transceiver() : RFM69{RF69_SPI_CS, RF69_IRQ_PIN, true, nullptr} {
    this->initialize(RF69_915MHZ, static_cast<uint8_t>(random(2, 253)),
                     NETWORK_ID);
  }

  // public structures
  enum Mode : uint8_t { Default = 0, Calibration = 1, Off = 2 };

  struct ReceivedData {
    Transceiver::Mode mode{Transceiver::Mode::Default};
  };

  struct TransmittedData {
    // these are required
    uint8_t currentMode{Transceiver::Mode::Default};
    // these are optional
    uint16_t soilLevel{UINT16_MAX};
    uint16_t temperature{UINT16_MAX};
    uint16_t batteryLevel{UINT16_MAX};
  };

  // public methods
  int Send(const TransmittedData &data);
  int Receive(ReceivedData &data);

  // public defines
  static constexpr uint8_t GATEWAY_ID{1};
  static constexpr uint8_t NODE_ID{2};
  static constexpr uint8_t NETWORK_ID{100};
};

#endif // TRANSCEIVER_HPP defined
