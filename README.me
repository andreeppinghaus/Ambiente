Classe sobre o chip HMC5883L

  Ambiente.h - Biblioteca com a Classe que define temperatura, altura, pressao atmosferica
  Author: André Eppinghaus
  Data: 04/09/2016
  Instrucoes: README.txt

Adaptacoes dos sites:

Adaptacoes : Arduino e Cia - http://www.arduinoecia.com.br/2014/09/sensor-gy-80-acelerometro-bussola-barometro.html

 Based largely on code by  Jim Lindblom
 Get pressure, altitude, and temperature from the BMP085.
 Serial.print it out at 9600 baud to serial monitor.

Modo de usar:

Instalação: 
Baixe as seguintes bibliotecas: 

https://github.com/manifestinteractive/arduino/tree/master/Libraries/HMC5883L

Programa de exemplo de uso para a utilização das bibliotecas Ambiente, Giroscopio e :


// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>

// controle da bussola
#include <Bussola.h>

// controle do giroscopio
#include <Giroscopio.h>

// controle do ambiente
#include <Ambiente.h>

Bussola bussola;
Giroscopio giro;
Ambiente ambiente;

void setup()
{
    // Initialize the serial port.
  Serial.begin(9600);
  Wire.begin(); //necessrio para o funcionamnto da bussola

  ambiente.setup(); 
  
  giro.setup();
  bussola.setup();// tem que ser por ultimo pois esta fechando o Wire.h

   
}

void loop()
{
  
  // Chama a rotina que calcula a temperatura
  // Esta rotina DEVE ser executada primeiro
  float temperature = ambiente.bmp085GetTemperature(ambiente.bmp085ReadUT());
 
  Serial.print("Temperatura: ");
  // Mostra a temperatura com 2 casas decimais
  Serial.print(temperature, 2); 
  Serial.println(" C");
  
 /// Chama a rotina que calcula a pressao
  float pressure = ambiente.bmp085GetPressure(ambiente.bmp085ReadUP());
  // Chama a rotina que calcula atmosfera
  float atm = pressure / 101325; 
  // Chama a rotina que calcula a altitude
  float altitude = ambiente.calcAltitude(pressure); 
 

  Serial.print("Pressao: ");
  Serial.print(pressure, 0); 
  Serial.println(" Pa");

  Serial.print("Atmosfera padrao : ");
  // Mostra o valor com 4 casas decimais
  Serial.println(atm, 4); //display 4 decimal places

  Serial.print("Altitude: ");
  // Mostra o valor com 2 casas decimais
  Serial.print(altitude, 2); 
  Serial.println(" M");

  Serial.println();

  Serial.println();
  
 Serial.print(" Graus   \t"); //ok
 Serial.print(bussola.getGraus());//ok
 Serial.println();
 
 giro.getGyroValues(); //calcula os valores

 Serial.print("X:");
 Serial.print(giro.getX()); //pega eixo X

 Serial.print(" Y:"); 
 Serial.print(giro.getY()); //pega eixo Y

  Serial.print(" Z:");
  Serial.println(giro.getZ()); //pega eixo Z
  
 delay(3000);
  
}
