/*
 Arduino Library for Sonmicro SM125 RFID reader (over I2C protocol)
 go to http://www.sonmicro.com/en/index.php?option=com_content&view=article&id=48&Itemid=64 for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created July 2013
 by Jonathan Ruiz de Garibay

 */ 

#include "Arduino.h"
#include "SM125.h"
#include <Wire.h>

//#define SM125_DEBUG

//
// begin
//
// This library use I2C protocol so, it is necesary to specified an I2C address.
boolean SM125::begin(uint8_t address){

	//save address, init outputs and I2C
	_address = address;
	_dreadyPin = 0xFF;
	_outputValues = 0x00;
	Wire.begin();
}

boolean SM125::begin(uint8_t address, uint8_t dreadyPin){

	//save address, init outputs and I2C
	_address = address;
	_dreadyPin = dreadyPin;
	pinMode(_dreadyPin, INPUT);
	_outputValues = 0x00;
	Wire.begin();
}

//
// anyTag
//
// Check Dready pin from sm125 module and return true if this pin is active
// This function need pin Dready is declared
boolean SM125::anyTag() {

	if (_dreadyPin == 0xFF)
		return false;
	return digitalRead(_dreadyPin);
}

//
// readTag
//
// Read a RFID tag and return true or false if there is a tag or not, respectively.
boolean SM125::readTag(byte *tagId){

	//first, read SM125 state
	Wire.beginTransmission(_address);
	Wire.write(READ_TAG);
	Wire.requestFrom(_address, 1);
	Wire.endTransmission();

	delay(1);
	if ((Wire.available() == 1) && (Wire.read() == DATA_READY)){
		
		//read 5 bytes; the first and the last are unused
		Wire.requestFrom(_address, 5);
		Wire.endTransmission();
		
		delay(1);
		if (Wire.available() == 5){
			Wire.read();
			tagId[0] = Wire.read();
#ifdef SM125_DEBUG
	Serial.print("Data 0: ");
	Serial.println(tagId[0], HEX);
#endif
			tagId[1] = Wire.read();
#ifdef SM125_DEBUG
	Serial.print("Data 1: ");
	Serial.println(tagId[1], HEX);
#endif
			tagId[2] = Wire.read();
#ifdef SM125_DEBUG
	Serial.print("Data 2: ");
	Serial.println(tagId[2], HEX);
#endif
			Wire.read();
		}

		//read 5 bytes; only the first one is needed
		Wire.requestFrom(_address, 5);
		Wire.endTransmission();
		
		delay(1);
		if (Wire.available() == 5){
			tagId[3] = Wire.read();
#ifdef SM125_DEBUG
	Serial.print("Data 3: ");
	Serial.println(tagId[3], HEX);
#endif
			//el resto de bytes no se usan
			Wire.read();
			Wire.read();
			Wire.read();
			Wire.read();
		}
		return true;
	}
	else{
#ifdef SM125_DEBUG
	Serial.println("No tag available");
#endif
		return false;
	}
}

//
// writeOutput
//
// Set sm125 outputs pin to high or low.
void SM125::writeOutput(uint8_t output, uint8_t value){

	//get the new output status
	uint8_t tempValues = 0x00;
	if (output == 0){
		if (value == HIGH)
			tempValues = 0x01;
	}
	else{
		if (value == HIGH)
			tempValues = 0x02;
	}
	if (value == HIGH)
		tempValues = tempValues | _outputValues;
	else
		tempValues = tempValues & _outputValues;

	//calculate the checksum
	uint8_t checksum = WRITE_OUTPUT + tempValues;

	//send command
	Wire.beginTransmission(_address);
	Wire.write(WRITE_OUTPUT);
	Wire.write(tempValues);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(checksum);
	Wire.requestFrom(_address, 1);
	Wire.endTransmission();

	delay(1);
	if (Wire.available() == 1){
		byte request = Wire.read();
		if (request == COMMAND_OK){
#ifdef SM125_DEBUG
	Serial.println("Output Updated");
#endif
			_outputValues = tempValues;
		}
	}
}

//
// readInput
//
// Get the state of the sm125 input pin.
uint8_t SM125::readInput(){

	//Send command
	Wire.beginTransmission(_address);
	Wire.write(READ_INPUT);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(READ_INPUT);
	Wire.requestFrom(_address, 1);
	Wire.endTransmission();

	//read reply and evaluate
	delay(1);
	if (Wire.available() == 1){
		byte request = Wire.read();
		if (request == INPUT_LOW){
#ifdef SM125_DEBUG
	Serial.println("Input LOW");
#endif
			return 0x00;
		}
		else{
#ifdef SM125_DEBUG
	Serial.println("Input HIGH");
#endif
			return 0x01;
		}
	}
	return 0xFF;
}