#include <SoftwareSerial.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <OneWire.h>

/*
The program starts with clock signal defined by OCR1A registrer placed on void setup(). To turn off the clock, follow 
this options: x+6+cad.
PD6: ANALOG INPUT 6 IN+ comparator.
PD7: ANALOG INPUT 7 IN- comparator.
PB1: DIGITAL OUTPUT 9 Clock signal.
PB2: DIGITAL INPUT 10 RX.
PB3: DIGITAL OUTPUT 11 TX.
*/
int val,apin0=A0,apin1=A1,apin2=A2,apin3=A3,apin4=A4,apin5=A5,dpin2=2,dpin13=13,dpin9=9,compin0=6,compin1=7,s10,s11,s12,s13,s14,s15,s16,s17,s18,counter;
char op,clock_op,op_aux;
float celsius, fahrenheit;
SoftwareSerial mySerial(10,11,1); // RX, TX
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
  pinMode(dpin9,OUTPUT);  //0C1A.
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
  mySerial.begin(57600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
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
  Serial.print("\n\n 0 CAD0.\n 1 CAD1.\n 2 CAD2.\n 3 CAD3.\n 4 CAD4.\n 5 CAD5.\n 6 CLOCK OFF.\n 7 Fuel Rising/Droping.\n 8 One Wire. \n\n");
  
  switch(op){
    case '0':
    do{
      val=analogRead(apin0);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do.
    break;

    case '1':
    do{
      val=analogRead(apin1);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do.
    break;

    case '2':
    do{
      val=analogRead(apin2);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do.
    break;

    case '3':
    do{
      val=analogRead(apin3);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do.
    break;

    case '4':
    do{
      val=analogRead(apin4);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do.
    break;

    case '5':
    do{
      val=analogRead(apin5);
      Serial.println(val); 
      op=Serial.read();  
      }while(op!='x');// del do.
    break;

    case '6':
    TCCR1B=0b00000000;
    break;

    case '7':    
    Serial.print("Type x to end. You must wait until 4 minutes to end the loop.");
    counter=4; // calamp 4, TopFly 1.
    
    do{      
      //Raising.
      op_aux=Serial.read();
      for (int i=0;i<counter;i++){
        s10=62; //hex=3E  Prefix
        mySerial.write(s10);
        delay(10);

        s11=1; //hex=01   Sender network address
        mySerial.write(s11);
        delay(10);

        s12=7; //hex=07   Command code
        mySerial.write(s12);
        delay(10);

        s13=39; //hex=27    Temperature
        mySerial.write(s13);
        delay(10);

        s14=255; //hex=FF    User value 01
        mySerial.write(s14);
        delay(10);

        s15=15; //hex=0F   User value 02
        mySerial.write(s15);
        delay(10);

        s16=255; //hex=FF  Tech user value 01
        mySerial.write(s16);
        delay(10);

        s17=255; //hex=FF    Tech user value 02
        mySerial.write(s17);
        delay(10);

        s18=84; //hex=54    CRC
        mySerial.write(s18);
        delay(10);
        }//Rising.

        delay(60000); //1 minute.

        //Dropping.

      for(int i=0;i<counter;i++){
        s10=62; //hex=3E  Prefix
        mySerial.write(s10);
        delay(10);

        s11=1; //hex=01   Sender network address
        mySerial.write(s11);
        delay(10);

        s12=7; //hex=07   Command code
        mySerial.write(s12);
        delay(10);

        s13=35; //hex=23    Temperature
        mySerial.write(s13);
        delay(10);

        s14=220; //hex=DC    User value 01
        mySerial.write(s14);
        delay(10);

        s15=2; //hex=02   User value 02
        mySerial.write(s15);
        delay(10);

        s16=201; //hex=C9  Tech user value 01
        mySerial.write(s16);
        delay(10);

        s17=45; //hex=2D    Tech user value 02
        mySerial.write(s17);
        delay(10);

        s18=207; //hex=CF    CRC
        mySerial.write(s18);
        delay(10);
        }//Dropping.

        delay(60000); //1 minute.
      }while(op_aux!='x');    
    break;  

    case '8':
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
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end.
    
    delay(1000);     // maybe 750ms is enough, maybe not.
    // we might do a ds.depower() here, but the reset will take care of it.
    
    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);         // Read Scratchpad.

    Serial.print("Data = ");
    Serial.print(present, HEX);
    Serial.print(" ");
    for ( i = 0; i < 9; i++) {           // we need 9 bytes.
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
      raw = raw << 3; // 9 bit resolution default.
      if (data[7] == 0x10) {
        // "count remain" gives full 12 bit resolution.
        raw = (raw & 0xFFF0) + 12 - data[6];
      }
    } else {
      byte cfg = (data[4] & 0x60);
      // at lower res, the low bits are undefined, so let's zero them.
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms.
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms.
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms.
      //// default is 12 bit resolution, 750 ms conversion time.
    }
    celsius = (float)raw / 16.0;
    fahrenheit = celsius * 1.8 + 32.0;
    Serial.print("Temperature = ");
    Serial.print(celsius);
    Serial.print("Celsius, ");
    Serial.print(fahrenheit);
    Serial.println("Fahrenheit");
    break;    

    default:
    Serial.print(" Fin");    
  }// Switch.  
 
}// SerialEvent.