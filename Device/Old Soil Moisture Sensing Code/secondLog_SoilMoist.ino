
const int AirValue = 564;   //you need to replace this value with Value_1
const int WaterValue = 293;  //you need to replace this value with Value_2

int soilMoistureValue = 0;
int soilmoisturepercent = 0;

unsigned long curSeconds = 0;

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  Serial.println(" Time (s) , Analog Reading , Percent Value ");
}

void loop() {
soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
curSeconds = millis()/1000;
Serial.print(curSeconds);

Serial.print(" , ");
Serial.print(soilMoistureValue);

soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
Serial.print(" , ");
Serial.println(soilmoisturepercent);

  delay(1000);
}
