#include <avr/io.h>
#include <avr/interrupt.h>
#include <OneWire.h>

/*
The program starts with clock signal defined by OCR1A registrer placed on void setup(). To turn off the clock, follow 
this options: x+6+cad.
*/
int val,apin0=A0,apin1=A1,apin2=A2,apin3=A3,apin4=A4,apin5=A5,dpin2=2,dpin13=13,dpin9=9,compin0=6,compin1=7;
char op,clock_op;
float celsius, fahrenheit;
OneWire  ds(10);

byte i;
byte present = 0;
byte type_s;
byte data[9];
byte addr[8];

ISR(ANALOG_COMP_vect){
  cli();
  digitalWrite(dpin13,LOW);
  op='a';
}

ISR(TIMER1_COMPA_vect){
  cli();
  digitalWrite(dpin2,HIGH);
  sei();
}

void setup() {
  Serial.begin(9600);
  pinMode(dpin13,OUTPUT);
  pinMode(dpin2,OUTPUT);
  pinMode(dpin9,OUTPUT);  //0C1A
  pinMode(compin0,INPUT);
  pinMode(compin1,INPUT);
  //Clock:  
  TCCR1A=0;
  TCCR1B=0;
  OCR1A=15264; //1Hz at 1024 prescaler.
  TCCR1A|=(1<<COM1A0);
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS12)|(1<<CS10);
  TIMSK1 |= (1 << OCIE1A);
  ACSR=bit(ACIE);
  sei();
  // put your setup code here, to run once:
}// del setup.

void loop() {
  digitalWrite(dpin13,HIGH);
  if(op=='a'){
    Serial.print("Pico de voltaje detectado, presione x para reestablecer.");
    do{
      op=Serial.read();
      sei();
    }while(op!='x');    
  }// del if.
  // put your main code here, to run repeatedly:  
}// del loop.

void serialEvent(){
  op=Serial.read();
  Serial.print("0 CAD0, 1 CAD1, 2 CAD2, 3 CAD3, 4 CAD4, 5 CAD5 6 CLOCK OFF 7 One Wire.");
  
  switch(op){
    case '0':
    do{
      val=analogRead(apin0);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do
      break;

    case '1':
    do{
      val=analogRead(apin1);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do
      break;

    case '2':
    do{
      val=analogRead(apin2);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do
      break;

    case '3':
    do{
      val=analogRead(apin3);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do
      break;

    case '4':
    do{
      val=analogRead(apin4);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do
      break;

    case '5':
    do{
      val=analogRead(apin5);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do
      break;

    case '6':
    TCCR1B=0b00000000;
      break;

    case '7':
      if ( !ds.search(addr)) {
        Serial.println("No more addresses.");
        Serial.println();
        ds.reset_search();
        delay(250);
        //return;
      }
      Serial.print("ROM =");
      for( i = 0; i < 8; i++) {
        Serial.write(' ');
        Serial.print(addr[i], HEX);
      }

      if (OneWire::crc8(addr, 7) != addr[7]) {
        Serial.println("CRC is not valid!");
        //return;
      }
      Serial.println();

        switch (addr[0]) {

          case 0x10:
          Serial.println("Chip = DS18S20");  // or old DS1820
          type_s = 1;
          break;

          case 0x42:
          Serial.println("TSO Mobile.");
          type_s = 0;
          break;

          case 0x22:
          Serial.println("Chip = DS1822");
          type_s = 0;
          break;

          case 0x28:
          Serial.println("Chip = Temperature Sensor");
          type_s=0;
          break;

          default:
          Serial.println("Device is not a DS18x20 family device.");
          type_s=0;
          //return;
        
        }

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end
    
    delay(1000);     // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.
    
    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);         // Read Scratchpad

    Serial.print("  Data = ");
    Serial.print(present, HEX);
    Serial.print(" ");
    for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.print(" CRC=");
    Serial.print(OneWire::crc8(data, 8), HEX);
    Serial.println();

    // Convert the data to actual temperature
    // because the result is a 16 bit signed integer, it should
    // be stored to an "int16_t" type, which is always 16 bits
    // even when compiled on a 32 bit processor.
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s) {
      raw = raw << 3; // 9 bit resolution default
      if (data[7] == 0x10) {
        // "count remain" gives full 12 bit resolution
        raw = (raw & 0xFFF0) + 12 - data[6];
      }
    } else {
      byte cfg = (data[4] & 0x60);
      // at lower res, the low bits are undefined, so let's zero them
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
      //// default is 12 bit resolution, 750 ms conversion time
    }
    celsius = (float)raw / 16.0;
    fahrenheit = celsius * 1.8 + 32.0;
    Serial.print("  Temperature = ");
    Serial.print(celsius);
    Serial.print(" Celsius, ");
    Serial.print(fahrenheit);
    Serial.println(" Fahrenheit");
    break;

    default:
    Serial.print(" Fin");    
    }// del switch.  
 
}// del serialEvent
