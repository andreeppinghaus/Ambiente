/*
  Ambiente.h - Biblioteca com a Classe que define temperatura, altura, pressao atmosferica
  *
  * http://www.arduinoecia.com.br/2014/09/sensor-gy-80-acelerometro-bussola-barometro.html
  * 
  *  	

// Programa : Teste BMP085 - Barometro / temperatura
// Adaptacoes : Arduino e Cia

 Based largely on code by  Jim Lindblom
 Get pressure, altitude, and temperature from the BMP085.
 Serial.print it out at 9600 baud to serial monitor.

Modo de usar:
Setup(){
  Wire.begin(); //necessrio para o funcionamnto da bussola
  ambiente.setup();
 
   }
   * 
  Loop() {
  * ambiente.bmp085GetTemperature(ambiente.bmp085ReadUT()); //temperatura
  * ambiente.bmp085GetPressure(ambiente.bmp085ReadUP());  //pressao
  * ambiente.calcAltitude(pressure);  //altitude
  * }
   

*/
#include "/usr/share/arduino/libraries/Wire/Wire.h" //verificar o local correto do Wire.h
#include "Arduino.h"
#include "Ambiente.h"

void Ambiente::setup() {
	
//	this->begin();
	
	Serial.begin(9600);
	
	Serial.println("configurando Ambiente");
	 this->bmp085Calibration();
  Serial.println("terminou");
	
}


// Armazena todos os valores de calibracao do BMP085 em 
// variaveis globais. Valores de calibracao sao exigidos para
// calcular temperatura e pressao
// Esta funcao deve ser chamada/acionada no inicio do programa
void Ambiente::bmp085Calibration()
{
  this->ac1 = bmp085ReadInt(0xAA);
  this->ac2 = bmp085ReadInt(0xAC);
  this->ac3 = bmp085ReadInt(0xAE);
  this->ac4 = bmp085ReadInt(0xB0);
  this->ac5 = bmp085ReadInt(0xB2);
  this->ac6 = bmp085ReadInt(0xB4);
  this->b1 = bmp085ReadInt(0xB6);
  this->b2 = bmp085ReadInt(0xB8);
  this->mb = bmp085ReadInt(0xBA);
  this->mc = bmp085ReadInt(0xBC);
  this->md = bmp085ReadInt(0xBE);
}

// Calcula a temperatura em graus C
float Ambiente::bmp085GetTemperature(unsigned int ut)
{
  long x1, x2;

  x1 = (((long)ut - (long)this->ac6)*(long)this->ac5) >> 15;
  x2 = ((long)this->mc << 11)/(x1 + md);
  b5 = x1 + x2;

  float temp = ((b5 + 8)>>4);
  temp = temp /10;

  return temp;
}

// Calcula a pressao. Os valores de calibracao devem ser conhecidos
// b5 tambem eh exigido, logo a funcao bmp085GetTemperature(...) deve
// ser executada primeiro.
// Funcao retorna pressao em unidades de Pa
long Ambiente::bmp085GetPressure(unsigned long up){
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;

  b6 = b5 - 4000;
  // Calcula B3
  x1 = (this->b2 * (b6 * b6)>>12)>>11;
  x2 = (this->ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)this->ac1)*4 + x3)<<OSS) + 2)>>2;

  // Calcula B4
  x1 = (this->ac3 * b6)>>13;
  x2 = (this->b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (this->ac4 * (unsigned long)(x3 + 32768))>>15;

  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;

  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;

  long temp = p;
  return temp;
}

// Read 1 byte from the BMP085 at 'address'
char Ambiente::bmp085Read(unsigned char address)
{
  unsigned char data;

  this->beginTransmission(BMP085_ADDRESS);
  this->write(address);
  this->endTransmission();

  this->requestFrom(BMP085_ADDRESS, 1);
  while(!this->available())
    ;

  return this->read();
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int Ambiente::bmp085ReadInt(unsigned char address)
{
  unsigned char msb, lsb;

  this->beginTransmission(BMP085_ADDRESS);
  this->write(address);
  this->endTransmission();

  this->requestFrom(BMP085_ADDRESS, 2);
  while(this->available()<2)
    ;
  msb = this->read();
  lsb = this->read();

  return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int Ambiente::bmp085ReadUT(){
  unsigned int ut;

  // Write 0x2E into Register 0xF4
  // This requests a temperature reading
  this->beginTransmission(BMP085_ADDRESS);
  this->write(0xF4);
  this->write(0x2E);
  this->endTransmission();

  // Wait at least 4.5ms
  delay(5);

  // Read two bytes from registers 0xF6 and 0xF7
  ut = this->bmp085ReadInt(0xF6);
  return ut;
}

// Read the uncompensated pressure value
unsigned long Ambiente::bmp085ReadUP(){

  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;

  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  this->beginTransmission(BMP085_ADDRESS);
  this->write(0xF4);
  this->write(0x34 + (OSS<<6));
  this->endTransmission();

  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));

  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  msb = this->bmp085Read(0xF6);
  lsb = this->bmp085Read(0xF7);
  xlsb = this->bmp085Read(0xF8);

  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);

  return up;
}

void Ambiente::writeRegister(int deviceAddress, byte address, byte val) {
  this->beginTransmission(deviceAddress); // start transmission to device 
  this->write(address);       // send register address
  this->write(val);         // send value to write
  this->endTransmission();     // end transmission
}

int Ambiente::readRegister(int deviceAddress, byte address){

  int v;
  this->beginTransmission(deviceAddress);
  this->write(address); // register to read
  this->endTransmission();

  this->requestFrom(deviceAddress, 1); // read a byte

  while(!this->available()) {
    // waiting
  }

  v = this->read();
  return v;
}

float Ambiente::calcAltitude(float pressure)
{
  float A = pressure/101325;
  float B = 1/5.25588;
  float C = pow(A,B);
  C = 1 - C;
  C = C /0.0000225577;

  return C;
}

