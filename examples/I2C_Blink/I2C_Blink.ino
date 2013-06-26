#include <Wire.h>
#include <SM125.h>

#define SM125_ADDRESS 0x46

SM125 sm125;

void setup() {

  Serial.begin(9600);
  Serial.println("Start Blink Demo:");
  
  sm125.begin(SM125_ADDRESS);
}

void loop() {

  sm125.writeOutput(1, 1);
  delay(200);
  sm125.writeOutput(1, 0);
  delay(600);
}
