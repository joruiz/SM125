/*
  SimpleRead
  Read RFID tag Id.
 
  This example code is in the public domain.
 */
 
#include <Wire.h>
#include <SM125.h>

#define SM125_ADDRESS 0x46

SM125 sm125;
String tagId;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Start Simple Read Demo:");

  sm125.begin(SM125_ADDRESS);
}

void loop() {

  delay(500);
  tagId = sm125.readTag();
  if (!tagId.equals(""))
    Serial.println("Tag leido: " + tagId);
  else
    Serial.println("No Tag");
}
