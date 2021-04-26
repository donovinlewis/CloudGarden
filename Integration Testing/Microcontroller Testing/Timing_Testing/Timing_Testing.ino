
int mode = 0;
int cal = 0;
unsigned long durStamp, curSec, duration = 0;

void setup() {
}

void loop() {

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
