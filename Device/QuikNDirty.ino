/* Some bullshit Donovin Lewis made
   Real talk tho

*/

#include "LowPower.h"

#define LENGTH 9

#define SOILI PD5
#define SOILO PC0

#define THERMI PD4
#define THERMO PC1

int mode = 1;
int cal = 0;
unsigned long durStamp, curSec, duration = 0;

int calAir = 564;
int calWat = 293;
int soilVal, soilPct = 0;

const int A = 1.009249522e-03;
const int B = 2.378405444e-04;
const int C = 2.019202697e-07;

int tempVal = 0;

void setup() {
  Serial.begin(9600);

  pinMode(SOILI, OUTPUT);
  pinMode(SOILO, INPUT);

  pinMode(THERMI, OUTPUT);
  pinMode(THERMO, INPUT);
}

void loop() {
  /*
    if (Serial.available() > LENGTH-1) {
      Serial.readBytes(rec_msg, LENGTH);

      //Prints a serial message containing the serial values sent from the master for debugging
      for (int i = 0; i < LENGTH; i++) {
        Serial.print(rec_msg[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  */

  digitalWrite(SOILI, HIGH);
  digitalWrite(THERMI, HIGH);
  delay(100);

  soilVal = analogRead(SOILI);
  soilPct = map(soilVal, calAir, calWat, 0, 100);

  tempVal = therm(analogRead(THERMO));

  if (mode == 0) duration = 3600;

  if (mode == 1) duration = 5;

  if (mode == 2) {
    duration = 1;
    if (cal == 1) calAir = soilVal;
    if (cal == 2) calWat = soilVal;
    if (cal != 1 || cal != 2) mode = 0;
  }

  durStamp = millis();
  duration  *= 12.5; //Converts to millis with sleep time factored in

  while ((millis() - durStamp) < duration) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void printVal(){
    curSec = millis()/1000;
    Serial.print(curSec);
    Serial.print(" , ");
    Serial.print(soilVal);
    Serial.print(" , ");
    Serial.print(soilPct);
    Serial.print(" , ");
    Serial.println(tempVal);
}

int therm(int V0) {
  float logRT, T, TC, TF = 0;
  logRT = log(10000 * ((1024 / V0) - 1));
  T = (1 / (A + B * logRT + C * logRT * logRT * logRT));
  TC = T - 273.15;
  TF = (TC * 1.8) + 32;
  return TF;
}
