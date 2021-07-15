/*
*Code written by Austin Peay State University student Rashaad Washington 2021
*Potentiometer v1.0
*Last changes made on 7/15/2021 at 14:24 CDT
 */
float RT = 5000;// the potentiometer's resistance is valued at 5kΩ 
float R;// the unknown resistance value R

int potPin = A5; // potentiometer is connected to analog pin 5
int potValue; // variable used to store the value coming from the sensor
int percent; // variable used to store the percentage value

void setup() {
  Serial.begin(9600); // initialize the serial communication
}

void loop() {
  potValue = analogRead(potPin); // get a reading from the potentiometer, assign the name potValue
  Serial.println(potValue);
  /*
   * Lowest reading is near ~300 then jumps to ~790-800. Possible reasons why...
   * May need to tune potentiometer. It is more precise at ~875.
   */
  delay(2000); //wait 2 second(s)
  /* percent = map(potValue, 0, 1023, 0, 100); // convert reading (potValue) to a percentage
  float voltage = potValue * (5.0 / 1023.0);  //convert to voltage 
  R = ( voltage * RT)/5.0;   // get value of unknown resistance
  
  Serial.print("Analog Reading: "); // print out the analog value from A5
  Serial.print(potValue);
  Serial.print(", Voltage =");// prints the text "Voltage ="
  Serial.print(voltage);
  Serial.print("v, Resistance="); //prints the text "Resistance ="
  Serial.print(R);
  Serial.print(" ohms");
  Serial.print(", Percentage: "); // print out the percentage
  Serial.print(percent);
  Serial.println("%");

  */
}
