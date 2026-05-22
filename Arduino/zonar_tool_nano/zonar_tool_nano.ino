#include <OneWire.h>
int sensorPin = A0;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
char op;
int cont=0;
OneWire ds(10);

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial);
  Serial.print("1. Analog sensor A0. \n2. Fuel sensor. \n3. OneWire. \nx. Exit!\n");
}// void setup.

void loop() { 

  op=Serial.read();
  switch(op){
    case '1':
    do{
    // read the value from the sensor:
    sensorValue=analogRead(sensorPin);
    Serial.println(sensorValue);
    op=Serial.read();
    }while(op!='x');
    Serial.print("\n1. Analog sensor A0. \n2. Fuel sensor. \n3. OneWire. \nx. Stop&Exit!\n");
    break;

    case '2':
    Serial.print("Rising!");
    Serial1.write(06); //HEX=3E
    delay(10);
    //Sender network address.
    Serial1.write(64); //HEX=01
    delay(10);
    //Command code.
    Serial1.write(136);//HEX=07
    delay(10);
    //Temperature.
    Serial1.write(52); //HEX=27
    delay(2000);
    //User value of fuel level 1
    Serial1.write(58); //HEX=FF
    delay(10);
    //User value of fuel level 2
    Serial1.write(96); //HEX=0F
    delay(10);
    //Technological value of fuel level 1
    Serial1.write(152);//HEX=FF
    delay(10);
    //Technological value of fuel level 2
    Serial1.write(141); //HEX=FF
    delay(2000);
    //CRC.
    Serial1.write(59); //HEX=54
    delay(2000);

    Serial.print("Droping!");
    Serial1.write(06); //HEX=3E
    delay(10);
    //Sender network address.
    Serial1.write(64); //HEX=01
    delay(10);
    //Command code.
    Serial1.write(136);//HEX=07
    delay(10);
    //Temperature.
    Serial1.write(52); //HEX=23
    delay(2000);
    //User value of fuel level 1
    Serial1.write(58); //HEX=DC
    delay(10);
    //User value of fuel level 2
    Serial1.write(96); //HEX=02
    delay(10);
    //Technological value of fuel level 1
    Serial1.write(152);//HEX=C9
    delay(10);
    //Technological value of fuel level 2
    Serial1.write(141); //HEX=2D
    delay(2000);
    //CRC.
    Serial1.write(59); //HEX=CF
    delay(2000);
    Serial.print("\n1. Analog sensor A0. \n2. Fuel sensor. \n3. OneWire. \nx. Stop&Exit!\n");
    do{
    op=Serial.read();
    }while(op!='x');
    break;

    case '3':    
    byte i;
    byte present = 0;
    byte type_s;
    byte data[9];
    byte addr[8];
    float celsius, fahrenheit;
    
    if ( !ds.search(addr)) {
      Serial.println("No more addresses.");
      Serial.println();
      ds.reset_search();
      delay(250);
      //return;                                                 Commented
    }// if
    
    Serial.print("ROM =");
    for( i = 0; i < 8; i++) {
      Serial.write(' ');
      Serial.print(addr[i], HEX);
    }// if

    if (OneWire::crc8(addr, 7) != addr[7]) {
        Serial.println("CRC is not valid!");
        //return;                                               Commented
    }// if
    Serial.println();
  
    // the first ROM byte indicates which chip
    switch (addr[0]) {
      case 0x10:
        Serial.println("  Chip = DS18S20");  // or old DS1820
        type_s = 1;
        break;
      case 0x42:
        Serial.println("  Chip = DS18B20");
        type_s = 0;
        break;
      case 0x28:
        Serial.println("  Chip = DS1822");
        type_s = 0;
        break;
      default:
        Serial.println("Device is not a DS18x20 family device.");
        //return;                                               Commented
    }// switch 

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end
    
    delay(1000);     // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.
    
    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);         // Read Scratchpad

    Serial.print("Data = ");
    Serial.print(present, HEX);
    Serial.print(" ");
    for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }// for
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
      }// if
    } else {
      byte cfg = (data[4] & 0x60);
      // at lower res, the low bits are undefined, so let's zero them
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
      //// default is 12 bit resolution, 750 ms conversion time
    }// if - else
    celsius = (float)raw / 16.0;
    fahrenheit = celsius * 1.8 + 32.0;
    Serial.print("Numeric data = ");
    Serial.print(celsius);
    //Serial.print(" Celsius, ");
    //Serial.print(fahrenheit);
    //Serial.println(" Fahrenheit");    
    Serial.print("\nPress reset on the device to test other device!");
    Serial.print("\n1. Analog sensor A0. \n2. Fuel sensor. \n3. OneWire. \nx. Stop&Exit!\n");
    do{
    op=Serial.read();
    }while(op!='x');
    break;
    }// switch
  
}//void loop

