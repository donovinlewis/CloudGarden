#ifndef MAIN_H
#define MAIN_H

//Common libraries needed across sections
#include "Arduino.h"

//Custom Libraries
#include "sms.h"
//#include "batmon.h"
#include "transceiver.h"

//Microcontroller Pin Definitions
constexpr struct PINS
{
    static constexpr uint8_t SOILM = A0;
    static constexpr uint8_t TEMPR_ADC = PC1; // uncertain
    static constexpr uint8_t TEMPR_PWR = PD7; // uncertain
};


#endif