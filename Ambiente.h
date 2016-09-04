/*
  Ambiente.h -  Biblioteca para uso do magnetrometro
  
*/
#ifndef Ambiente_h
#define Ambiente_h
#include "Arduino.h"
#include "/usr/share/arduino/libraries/Wire/Wire.h"

//Define o endereco I2C do BMP085 - 0x77 ou 119 em decimal
#define BMP085_ADDRESS 0x77  

const unsigned char OSS = 0;  // Oversampling Setting

class Ambiente : public TwoWire
{
  public:
    
	void setup();
	void  bmp085Calibration();
	float bmp085GetTemperature(unsigned int ut);
	long  bmp085GetPressure(unsigned long up);
	char  bmp085Read(unsigned char address);
	int   bmp085ReadInt(unsigned char address);
	unsigned int bmp085ReadUT();
	unsigned long bmp085ReadUP();
	void writeRegister(int deviceAddress, byte address, byte val) ;
	int readRegister(int deviceAddress, byte address);
	float calcAltitude(float pressure);
	
   
  private:

	// Calibration values
	int ac1;
	int ac2;
	int ac3;
	unsigned int ac4;
	unsigned int ac5;
	unsigned int ac6;
	int b1;
	int b2;
	int mb;
	int mc;
	int md;
	
	// b5 is calculated in bmp085GetTemperature(...), this 
// variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
	long b5; 

};
#endif
