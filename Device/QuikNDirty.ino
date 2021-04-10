/* Some bullshit Donovin Lewis made
   Real talk tho

*/

#include "LowPower.h"

//#define LENGTH 9

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

int battVolts = 0;

void setup() {
  //Serial.begin(9600);

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

  for (int i = 0; i <= 2; i++) battVolts += getBandgap();
  battVolts = battVolts / 3;

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

void printVal() {
  curSec = millis() / 1000;
  Serial.print(curSec);
  Serial.print(" , ");
  Serial.print(soilVal);
  Serial.print(" , ");
  Serial.print(soilPct);
  Serial.print(" , ");
  Serial.print(tempVal);
  Serial.print(" , ");
  Serial.println(battVolts);
}

int therm(int V0) {
  float logRT, T, TC, TF = 0;
  logRT = log(10000 * ((1024 / V0) - 1));
  T = (1 / (A + B * logRT + C * logRT * logRT * logRT));
  TC = T - 273.15;
  TF = (TC * 1.8) + 32;
  return TF;
}

int getBG(void) {
  const long InternalReferenceVoltage = 1050L;  // Adust this value to your specific internal BG voltage x1000
  // REFS1 REFS0          --> 0 1, AVcc internal ref.
  // MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)
  ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
  // Start a conversion
  ADCSRA |= _BV( ADSC );
  // Wait for it to complete
  while ( ( (ADCSRA & (1 << ADSC)) != 0 ) );
  // Scale the value
  int results = (((InternalReferenceVoltage * 1024L) / ADC) + 5L) / 10L;
  return results;
}
