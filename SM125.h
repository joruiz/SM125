/*
 Arduino Library for Sonmicro SM125 RFID reader (over I2C protocol)
 go to http://www.sonmicro.com/en/index.php?option=com_content&view=article&id=48&Itemid=64 for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created July 2013
 by Jonathan Ruiz de Garibay

 */ 

#ifndef SM125_h
#define SM125_h

#include "Arduino.h"

#define READ_TAG		0x52
#define WRITE_OUTPUT	0x62
#define READ_INPUT		0x63

#define COMMAND_OK		0x6F
#define DATA_READY		0x6E
#define INPUT_LOW		0x70
#define INPUT_HIGH		0x71

class SM125
{
	public:
		boolean begin(uint8_t address);
		boolean readTag(byte *tagId);
		void writeOutput(uint8_t output, uint8_t value);
		boolean readInput();

	private:
		int _address;
		uint8_t _outputValues;
};

#endif