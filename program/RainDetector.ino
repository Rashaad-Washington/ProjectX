#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SparkFunDS1307RTC.h> //RTC module
#include <max6675.h> //thermocouple
#include <stdio.h> //for sprintf
#include <stdlib.h> //for rand()
/*
  Code written by Austin Peay State University student Rashaad Washington 2021
  RainDetector v1.0
  Last changes made on 12/11/2021 at 5:39 CDT
*/
//****************************
File myFile;

int soPin = 4;// SO=Serial Out
int csPin = 5;// CS = chip select CS pin
int sckPin = 6;// SCK = Serial Clock pin
const int chipSelect = 10;
const int motor3 = 3; //Motor on Digital pin 3
MAX6675 Module(sckPin, csPin, soPin);
char timeBuffer[20];
char dateBuffer[20];
const int rainSensor = A0; //Analog A0
bool removed;

void setup() {
  rtc.begin();
  rtc.autoTime();
  pinMode(rainSensor, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(motor, OUTPUT);
  Serial.begin(9600); //Think of this as the Begin all above
  //*************************************************

  while (!Serial);
  Serial.println("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    Serial.println("Please ensure an SD card is inserted");
    while (!SD.begin(4));
  }
  myFile = SD.open("test.csv", FILE_WRITE);
  myFile.close();
  Serial.println("SD Card Found\n");
  removed = true;
} //End of VoidStart

void loop() {
  while (SD.begin(4)) {
    rtc.update();
    int value = rand() % 100; //DEBUG value: Wont need for actual program
    if (value > 50 ) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println(value);
      Serial.println("LED ON");
      writeToSDCard();
      Serial.println();
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println(value);
      Serial.println("LED OFF");
      writeToSDCard();
      Serial.println();
    }
    delay(5000); //this needs to be 10minutes;
  }
  if (!SD.begin(4)) {
    Serial.println("SD card removed");
    removed = true;
    while (!SD.begin(4));
  }
  Serial.println("SD Card found\n");
}

void printTime(char* buf1) {
  sprintf(buf1, "%02d:%02d:%02d,",  rtc.hour(), rtc.minute(), rtc.second());
  Serial.println(buf1);
  myFile.print(buf1);
}

void printDate(char* buf1) {
  sprintf(buf1, "%02d-%02d-%02d,", rtc.year(), rtc.month(), rtc.day());
  Serial.println(buf1);
  myFile.print(buf1);
}
void Rain() { //this consists of an int of 0,1 AND the value associated with
  int value = analogRead(rainSensor);
  if (value <= 500)
  {
    Serial.println("rainSensor value: " + value);
    Serial.println("Is NOT raining");
    myFile.print(String(0) + ",");
    myFile.print(String(value) + ",");
  } else if (value > 500) {
    Serial.println("rainSensor value: " + value);
    Serial.println("Is raining");
    myFile.print(String(1) + ",");
    myFile.print(String(value) + ",");
  }
}

float temperature() {
  return ((9 / 5) * (Module.readCelsius()) + 32);
}

void inserted() {
  if (removed) {
    myFile.print("1,");
    removed = false;
  } else if (!removed) {
    myFile.print("0,");
  }
}

void writeToSDCard() {
  myFile = SD.open("test.csv", FILE_WRITE);
  printDate(dateBuffer);
  printTime(timeBuffer);
  inserted();
  //Rain();
  myFile.println();
  myFile.close();
}
