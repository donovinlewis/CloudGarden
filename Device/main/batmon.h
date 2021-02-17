#ifndef BAT_H
#define BAT_H

#include <Arduino.h>
#include <Wire.h>

// MAX1720X register addresses
const int MAX1720X_ADDR = 0x36;
const int MAX1720X_STATUS_ADDR = 0x00; // Contains alert status and chip status
const int MAX1720X_VCELL_ADDR = 0x09; // Lowest cell voltage of a pack, or the cell voltage for a single cell
const int MAX1720X_REPSOC_ADDR = 0x06; // Reported state of charge
const int MAX1720X_REPCAP_ADDR = 0x05; // Reported remaining capacity
const int MAX1720X_TEMP_ADDR = 0x08; // Temperature
const int MAX1720X_CURENT_ADDR = 0x0A; // Battery current
const int MAX1720X_TTE_ADDR = 0x11; // Time to empty
const int MAX1720X_TTF_ADDR = 0x20; // Time to full
const int MAX1720X_CAPACITY_ADDR = 0x10; // Full capacity estimation
const int MAX1720X_VBAT_ADDR = 0xDA; // Battery pack voltage
const int MAX1720X_AVCELL_ADDR = 0x17; // Battery cycles
const int MAX1720X_COMMAND_ADDR = 0x60; // Command register
const int MAX1720X_CONFIG2_ADDR = 0xbb; // Command register

// Class for MAX17201 battery fuel gauges
class batMon
{
public:
	batMon();
    double getVoltage();
    double getSOC();
    double getTemperature();
    double getCurrent();
    double getCapacity();
    double getTTE();
    double getTTF();
    uint8_t reset();
private:
    uint16_t getStatus();
};

#endif