#ifndef TRANSCEIVER_HPP
#define TRANSCEIVER_HPP
// includes from LowPowerLab library
#include <LowPower.h>
#include <RFM69.h>

// standard library includes.
#include <cstdint>
#include <bitset>
#include <stdint.h>

// helper functions
static constexpr uint8_t MSByte(uint16_t i)
{
    return static_cast<uint8_t>(i & 0xFF00);
}

static constexpr uint8_t LSByte(uint16_t i)
{
    return static_cast<uint8_t>(i & 0x00FF);
}

class Transceiver : private RFM69
{
public:
    // constructor
    Transceiver(uint16_t nodeID, uint16_t networkID) : RFM69{RF69_SPI_CS, RF69_IRQ_PIN, true, nullptr}
    {
        this->initialize(RF69_915MHZ, nodeID, networkID);
    }

    // public structures
    enum Mode : uint8_t
    {
        DEFAULT = 0,
        CALIBRATION = 1,
        OFF = 2
    };

    struct ReceivedData
    {
        Mode mode{Mode::DEFAULT};
    };

    struct TransmittedData
    {
        // these are required
        uint8_t currentMode{Mode::DEFAULT};
        // these are optional
        uint16_t soilLevel{UINT16_MAX};
        uint16_t temperature{UINT16_MAX};
        uint16_t batteryLevel{UINT16_MAX};
    };

    // public methods
    int Send(TransmittedData &data);
    int Receive(ReceivedData &data);

    // public defines
    static constexpr uint8_t GATEWAY_ID{1};
};

#endif // TRANSCEIVER_HPP defined
