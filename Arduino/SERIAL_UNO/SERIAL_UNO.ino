#include <SPI.h>
int CS=3;
byte data=0x0D,rx;

//13 SCK
//12 MISO
//11 MOSI
//10 SS

/*setClockDivider(SPI_CLOCK_DIV2);   //8 MHz (considerando un modelo de 16 Mhz)
setClockDivider(SPI_CLOCK_DIV4);   //4 MHz
setClockDivider(SPI_CLOCK_DIV8);   //2 MHz
setClockDivider(SPI_CLOCK_DIV16);  //1 MHz
setClockDivider(SPI_CLOCK_DIV32);  //500 KHz
setClockDivider(SPI_CLOCK_DIV64);  //250 KHz
setClockDivider(SPI_CLOCK_DIV128); //125 KHz
SPI.beginTransaction (SPISettings (1000000, MSBFIRST, SPI_MODE0)); 
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_SPI_MOSI,OUTPUT);
  pinMode(PIN_SPI_MISO,INPUT);
  pinMode(PIN_SPI_SCK,OUTPUT);
  pinMode(PIN_SPI_SS,INPUT);
  pinMode(CS,OUTPUT);
  SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));
  //SPI.setClockDivider(SPI_CLOCK_DIV64);
  digitalWrite(CS,HIGH);
  Serial.println("Configuración cargada.");
}

void loop() {
  // put your main code here, to run repeatedly:   
  Serial.println("Iniciando...");
  digitalWrite(CS,LOW);
  SPI.begin();
  //SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0)); 
  //digitalWrite(CS,LOW);
  rx=SPI.transfer(data);
  delay(1000);
  Serial.println(rx);
  digitalWrite(CS,HIGH);
  delay(1000);  
  Serial.println("Finalizando...");
}