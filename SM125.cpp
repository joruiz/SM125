#include "Arduino.h"
#include "SM125.h"
#include "Wire.h"

//#define SM125_DEBUG

int _address;
uint8_t _outputValues = 0x00;

boolean SM125::begin(uint8_t address){

	_address = address;
	Wire.begin();

/*	//se envia el comando de lectura
	Wire.beginTransmission(_address);
	Wire.write(0x10);
	Wire.write(0x03);
	Wire.write(0x02);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x15);
	Wire.requestFrom(_address, 1);
	Wire.endTransmission();

	delay(1);
	if ((Wire.available() == 1) && (Wire.read() == 0x6B){
#ifdef SM125_DEBUG
	Serial.println("Read Mode Enabled");
#endif
		return true;
	}
	else{
#ifdef SM125_DEBUG
	Serial.println("Init Error");
#endif
		return false;
	}*/
}

boolean SM125::readTag(byte *tagId){

	//primero se lee el estado del lector RFID para saber si hay algo esperando
	Wire.beginTransmission(_address);
	Wire.write(0x52);
	Wire.requestFrom(_address, 1);
	Wire.endTransmission();

	delay(1);
	if ((Wire.available() == 1) && (Wire.read() == 0x6E)){
		
		//se obtienen los primeros 5 bytes
		Wire.requestFrom(_address, 5);
		Wire.endTransmission();
		
		delay(1);
		if (Wire.available() == 5){
			//el primero es siempre 1
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
			//el último indica si hay más bytes a recibir, en nuestro caso siempre
			Wire.read();
		}

		//se obtienen los últimos 5 bytes
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

void SM125::writeOutput(uint8_t output, uint8_t value){

	//se obtiene el estado de las salidas
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

	//se obtiene el checksum
	uint8_t checksum = 0x62 + tempValues;
	//se envia el comando
	Wire.beginTransmission(_address);
	Wire.write(0x62);
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
		if (request == 0x6F){
#ifdef SM125_DEBUG
	Serial.println("Output Updated");
#endif
			_outputValues = tempValues;
		}
	}
}

boolean SM125::readInput(){

	//se envia el comando
	Wire.beginTransmission(_address);
	Wire.write(0x63);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x00);
	Wire.write(0x63);
	Wire.requestFrom(_address, 1);
	Wire.endTransmission();

	delay(1);
	if (Wire.available() == 1){
		byte request = Wire.read();
		if (request == 0x70){
#ifdef SM125_DEBUG
	Serial.println("Input LOW");
#endif
			return LOW;
		}
		else{
#ifdef SM125_DEBUG
	Serial.println("Input HIGH");
#endif
			return HIGH;
		}
	}
}