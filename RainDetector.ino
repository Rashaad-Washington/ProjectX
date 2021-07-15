/*
*Code written by Austin Peay State University student Rashaad Washington 2021
*RainDetector v1.0
*Last changes made on 7/15/2021 at 14:24 CDT
 */
const int read = A0; //define water sensor
int value; //define water value

void setup() {
  // put your setup code here, to run once:
  pinMode(read, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(read); //reads the water sensor
  
  if (value <= 300)
  {
    Serial.println("Raining");
  }
  else if (value > 300 && value <= 700)
  {
    Serial.println("Sensor is wet");
  }
  else if (value > 700)
  {
    Serial.println("Is not raining");
  }
    Serial.println(value);
  delay(2000);
  
}
