#include <Wire.h>
#include <SM125.h>

#define SM125_ADDRESS 0x46

SM125 sm125;
byte tagId[4];

void setup() {
  
  Serial.begin(9600);
  Serial.println("Start Read Input Demo:");

  sm125.begin(SM125_ADDRESS);
}

void loop() {

  delay(500);
  Serial.print("Input state: ");
  if (sm125.readInput() == HIGH){
    Serial.println("HIGH");
  }
  else
    Serial.println("LOW");
}
