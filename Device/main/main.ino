#include "comSMS.h"

void setup(){
serialSoilInit();
}

void loop(){
    
updateSoilSensing(analogPin);
printSoilMoist();
delay(1000);

}
