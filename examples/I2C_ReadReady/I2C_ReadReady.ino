/*
  Read_Ready
 Read RFID tag Id when DREADY line is high
 
 This example code is in the public domain.
 */

/*
  DREADY pin to pin 2
 SCL pin to pin A5
 SDA pin to pin A4
 */

#include <Wire.h>
#include <SM125.h>

/*
  SM-125 DREADY pin to pin 2
 SM-125 SCL pin to pin A5
 SM-125 SDA pin to pin A4
 */

#define SM125_ADDRESS 0x46
#define DREADY 7

SM125 sm125;
String tagId;

void setup() {

  Serial.begin(9600);
  Serial.println("Start Simple Read Demo:");

  pinMode(DREADY, INPUT_PULLUP);

  sm125.begin(SM125_ADDRESS);

}

void loop() {

  if (digitalRead(DREADY) == HIGH) {
    tagId = sm125.readTag();
    if (!tagId.equals(""))
      Serial.println("Tag leido: " + tagId);
    else
      Serial.println("No Tag");
  }
  delay(10);
}


