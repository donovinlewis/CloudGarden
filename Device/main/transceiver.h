#ifndef TRANSCEIVER_HPP
#define TRANSCEIVER_HPP
#include <RadioLib.h>
#include <spi.h>

// standard library includes.
#include <stdint.h>

// helper functions
static constexpr uint8_t MSByte(uint16_t i) {
  return static_cast<uint8_t>((i & 0xFF00) >> 8);
}

static constexpr uint8_t LSByte(uint16_t i) {
  return static_cast<uint8_t>(i & 0x00FF);
}

class Transceiver : private RF69 {
public:
  // constructor
  // TODO: figure out which pins these need to be
  explicit Transceiver(uint8_t nodeId = 0x00)
      : RF69{new Module(SS, RFM69_INT, RFM69_RST)}, mNodeId{nodeId} {}

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
  int Send(const TransmittedData &data, uint8_t transmitToAddr = 0x00);
  int Receive(ReceivedData &data);
  int Sleep();
  int Awake();
  int Initialize() {
    radio.reset();
    delay(10);

    // initialize RF69 with default settings
    int status = printFailure(radio.begin(900.0, 100.0, 50.0, 125.0, 20, 16));

    // NOTE: some RF69 modules use high power output,
    //       those are usually marked RF69H(C/CW).
    //       To configure RadioLib for these modules,
    //       you must call setOutputPower() with
    //       second argument set to true.
    status |= printFailure(radio.setOutputPower(20, true));
    if (!mNodeId)
    {
      status |= printFailure(radio.disableAddressFiltering());
    }
    else
    {
      status |= printFailure(radio.setNodeAddress(mNodId));
    }
    
    uint8_t syncWord[4] = {0x01, 0x23, 0x45, 0x67};
    status |= printFailure(radio.setSyncWord(syncWord, 4));
    status |= printFailure(radio.enableSyncWordFiltering());
    status |= printFailure(radio.disableAES());
    status |= printFailure(radio.setCrcFiltering(false));
    status |= printFailure(radio.setDataShaping(RADIOLIB_SHAPING_0_5));
    status |= printFailure(radio.setEncoding(RADIOLIB_ENCODING_MANCHESTER));
    status |=
        printFailure(radio.variablePacketLengthMode(RF69_MAX_PACKET_LENGTH));
    return status;
  }

  // public defines
  // TODO: implement gateway and node ids
  static constexpr uint8_t GATEWAY_ID{1};
  static constexpr uint8_t RFM69_RST{8};
  static constexpr uint8_t RFM69_INT{3};

private:
  // private member variables
  bool isSleeping{false};
  const uint8_t mNodeId;

  int printFailure(int status) {
    if (Serial && status != ERR_NONE) {
      Serial.print("Failed error code = ");
      Serial.println(status);
    }
    return status;
  }
};

#endif // TRANSCEIVER_HPP defined
