#ifndef SM125_h
#define SM125_h

#include "Arduino.h"

class SM125
{
	public:
		boolean begin(uint8_t address);
		boolean readTag(byte *tagId);
		void writeOutput(uint8_t output, uint8_t value);
		boolean readInput();

	private:
	
};

#endif