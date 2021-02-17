#include "batmon.h"

// Initializes variables and the Wire library
batMon::batMon() { 
    Wire.begin(); 
}

// Returns a measurement of the voltage of the connected LiIon Polymer battery
double batMon::getVoltage()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_VCELL_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2,HIGH); //send stop
    uint16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
    double voltage = combined; //combine registers
    return voltage*0.078125; // //calculate actual value and return in mV
}

double batMon::getCurrent()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_CURENT_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2,HIGH); //send stop
    int16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
    double current = (double)combined*0.0015625/0.01;
    return current;//calculate actual value as 0.0015625 mV/Ohm
}

double batMon::getTemperature()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_TEMP_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2,HIGH); //send stop
    int16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
    double temperature = (double)combined/256;
    return temperature;
}

// Returns the relative state of charge of the connected LiIon Polymer battery
// as a percentage of the full capacity w/ resolution 1/256%
double batMon::getSOC()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_REPSOC_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2);
    uint16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
    double soc = combined; //combine registers
	return soc/256; //calculate actual value and return in %
}

// RepCap or reported capacity is a filtered version of the AvCap register that prevents large jumps in the reported value caused by changes in the application such as abrupt changes in temperature or load current. 
double batMon::getCapacity()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_REPCAP_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2);
    uint16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
	double capacity = (double)combined*0.005/0.01;
    return capacity;//calculate actual value as 0.005 mVh/Ohm
}

// The TTE register holds the estimated time to empty for the application under present temperature and load conditions 
double batMon::getTTE()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_TTE_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2);
    uint16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
	double capacity = (double)combined*5.625;
    return capacity;//calculate actual value as value*5.625s
}

// The TTF register holds the estimated time to full for the application under present conditions. 
double batMon::getTTF()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_TTF_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2);
    uint16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
	double capacity = (double)combined*5.625;
    return capacity;//calculate actual value as value*5.625s
}

// Status Register (000h) The Status register maintains all flags related to alert thresholds and battery insertion or removal.
uint16_t batMon::getStatus()
{
	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_STAT_ADDR);
	Wire.endTransmission(false);
	Wire.requestFrom(BAT_ADDR, (int)2);
    uint16_t combined = Wire.read()|(Wire.read()<<8); // LSB or-ed with MSB
	return combined;
}

// Reset procedure
uint8_t batMon::reset()
{
 	Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_COMMAND_ADDR);
	Wire.write(0x0f);
	Wire.write(0x00);
    Wire.endTransmission();
    delay(50);
    Wire.beginTransmission(BAT_ADDR);
	Wire.write(BAT_COMM2_ADDR);
	Wire.write(0x01);
	Wire.write(0x00);
	return Wire.endTransmission();
}