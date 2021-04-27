#ifndef BAT_H
#define BAT_H

//#include <Arduino.h>
//#include <Wire.h>

// MAX1720X register addresses
const int BAT_ADDR = 0x36;
const int BAT_STAT_ADDR = 0x00;  // Contains alert status and chip status
const int BAT_VCELL_ADDR = 0x09;   // Lowest cell voltage of a pack, or the cell voltage for a single cell
const int BAT_REPSOC_ADDR = 0x06;  // Reported state of charge
const int BAT_REPCAP_ADDR = 0x05;  // Reported remaining capacity
const int BAT_TEMP_ADDR = 0x08;    // Temperature
const int BAT_CURENT_ADDR = 0x0A;  // Battery current
const int BAT_TTE_ADDR = 0x11;     // Time to empty
const int BAT_TTF_ADDR = 0x20;     // Time to full
const int BAT_CAPACITY_ADDR = 0x10; // Full capacity estimation
const int BAT_VBAT_ADDR = 0xDA;    // Battery pack voltage
const int BAT_AVCELL_ADDR = 0x17;  // Battery cycles
const int BAT_COMMAND_ADDR = 0x60; // Command register
const int BAT_COMM2_ADDR = 0xbb;   // Command register

// Class for the battery monitoring fuel gauge
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
