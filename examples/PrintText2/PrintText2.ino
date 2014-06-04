#include <Wire.h>
#include <Display.h>

#define DISPLAY_ADDRESS  0x51

Display display;

void setup() {

  Serial.begin(9600);
  Serial.println("Master test program");

  display.begin(DISPLAY_ADDRESS);
  //wait for display initialization
  do {
    delay(50);
  }
  while(!display.isReady());
  //get firmware version
  int ver = display.getVersion();
  switch(ver)
  {
  case 0x10:
    Serial.println("Version: 1.0");
    break;
  }

}

void loop() {

  display.clear();
  display.printText("Hola y Adios", 6, 1, 0x00FF);
  delay(1000); 
}
