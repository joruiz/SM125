/*
  SimpleRead
  Read RFID tag Id.
 
  This example code is in the public domain.
 */
 
#include <Wire.h>
#include <SM125.h>

#define SM125_ADDRESS 0x46

SM125 sm125;
byte tagId[4];

void setup() {
  
  Serial.begin(9600);
  Serial.println("Start Simple Read Demo:");

  sm125.begin(SM125_ADDRESS);
}

void loop() {

  delay(500);
  if (sm125.readTag(tagId)){
    Serial.print("Tag leido: ");
    for (int i = 0; i < 4; i++){
      if (tagId[i] < 16)
        Serial.print('0');
      Serial.print(tagId[i], HEX);
    }
    Serial.println();
  }
  else
    Serial.println("No Tag");
}
