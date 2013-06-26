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
    Serial.print(tagId[0], HEX);
    Serial.print(tagId[1], HEX);
    Serial.print(tagId[2], HEX);
    Serial.println(tagId[3], HEX);
  }
  else
    Serial.println("No Tag");
}
