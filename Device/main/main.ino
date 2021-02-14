#include "comSMS.h"

soilMoist s;

void setup(){
s.serialSoilInit();
}

void loop(){
    
s.updateSoilSensing(SOILM);
s.printSoilMoist();
delay(1000);

}
