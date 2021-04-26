
#define THERMI PD4
#define THERMO PC1

const int A = 1.009249522e-03;
const int B = 2.378405444e-04;
const int C = 2.019202697e-07;

int tempVal = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(THERMI, OUTPUT);
  pinMode(THERMO, INPUT);
  digitalWrite(THERMI, HIGH);
}

void loop() {
tempVal = therm(analogRead(THERMO));
Serial.println(tempVal);
delay(1000);
}

int therm(int V0) {
  float logRT, T, TC, TF = 0;
  logRT = log(10000 * (1024 / (V0 - 1)));
  T = (1 / (A + B * logRT + C * logRT * logRT * logRT));
  TC = T - 273.15;
  TF = (TC * 1.8) + 32;
  return TF;
}
