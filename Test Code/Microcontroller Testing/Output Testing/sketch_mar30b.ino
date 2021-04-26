#define pin2 PD4

void setup() {
  // put your setup code here, to run once:
  pinMode(pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(pin2, LOW);
//  delay(2000);
  digitalWrite(pin2, HIGH);
  delay(2000);
}
