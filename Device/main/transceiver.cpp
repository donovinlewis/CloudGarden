#include "transceiver.h"

// pass in a defined TransmittedData
int Transceiver::Send(const TransmittedData &data, uint8_t transmitToAddr)
{
    Awake();
    uint8_t encoded_data[sizeof(TransmittedData)];
    encoded_data[0] = MSByte(data.soilLevel);
    encoded_data[1] = LSByte(data.soilLevel);
    encoded_data[2] = MSByte(data.temperature);
    encoded_data[3] = LSByte(data.temperature);
    encoded_data[4] = MSByte(data.batteryLevel);
    encoded_data[5] = LSByte(data.batteryLevel);
    encoded_data[6] = data.currentMode;
    
    // use RFM69.h send with requestAck = true just in case we ever want an ack.
    return transmit(encoded_data, sizeof(encoded_data), UINT32_MAX, transmitToAddr);
}

int Transceiver::Receive(ReceivedData &data)
{
    Awake();
    uint8_t bytes[] = {data.mode};
    // wait some very small amount of time
    int result = receive(bytes, sizeof(bytes), 0);
    data.mode = static_cast<Mode>(bytes[0]);
    return result;
}

int Transceiver::Sleep()
{
    isSleeping = true;
    return sleep();
}

int Transceiver::Awake()
{
    if (isSleeping)
    {
        isSleeping = false;
        return standby();
    }
    else
    {
        return 0;
    }
    
}
