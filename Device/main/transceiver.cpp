#include "transceiver.h"

// pass in a defined TransmittedData
int Transceiver::Send(const TransmittedData &data)
{
    uint8_t encoded_data[sizeof(TransmittedData)];
    encoded_data[0] = MSByte(data.soilLevel);
    encoded_data[1] = LSByte(data.soilLevel);
    encoded_data[2] = MSByte(data.temperature);
    encoded_data[3] = LSByte(data.temperature);
    encoded_data[4] = MSByte(data.batteryLevel);
    encoded_data[5] = LSByte(data.batteryLevel);
    encoded_data[6] = data.currentMode;
    
    // use RFM69.h send with requestAck = true just in case we ever want an ack.
    send(GATEWAY_ID, reinterpret_cast<void *>(encoded_data), sizeof(TransmittedData), true);
    int error = ACKReceived(GATEWAY_ID); // check to see if we got an ack
    return (error - 1);
}

int Transceiver::Receive(ReceivedData &data)
{
    // if (DATALEN == 1)
    // {
    //     data.mode = DATA;
    //     return 0;
    // }
    // else
    // {
    //     return -1;
    // }
}
