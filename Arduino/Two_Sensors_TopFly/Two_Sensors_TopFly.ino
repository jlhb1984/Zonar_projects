/*
  Software serial multiple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>
#include <stdio.h>
//#define ID 0x3101
int s10,s11,s12,s13,s14,s15,s16,s17,s18;

SoftwareSerial mySerial(10,11,1); // RX, TX

void setup() {
  // Open serial communications and wait for port to open: 
  mySerial.begin(57600);  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
   // set the data rate for the SoftwareSerial port  
   
}

void loop() {

    //Sensor 1.
    //for (int i=0;i<4;i++){
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
    //}//Of the sensor 1.

    delay(105000); //105 ms.

    //Sensor 2.

    //for(int i=0;i<4;i++){
      s10=62; //hex=3E  Prefix
      mySerial.write(s10);
      delay(10);

      s11=2; //hex=02   Sender network address
      mySerial.write(s11);
      delay(10);

      s12=7; //hex=07   Command code
      mySerial.write(s12);
      delay(10);

      s13=18; //hex=12    Temperature
      mySerial.write(s13);
      delay(10);

      s14=7; //hex=07    User value 01
      mySerial.write(s14);
      delay(10);

      s15=14; //hex=0E   User value 02
      mySerial.write(s15);
      delay(10);

      s16=121; //hex=79  Tech user value 01
      mySerial.write(s16);
      delay(10);

      s17=224; //hex=E0    Tech user value 02
      mySerial.write(s17);
      delay(10);

      s18=218; //hex=DA    CRC
      mySerial.write(s18);
      delay(10);
    //}//Of the sensor 2.

    delay(150000); //150 ms.

   
    /*
    mySerial.print(a);         // Print as an ASCII-encoded decimal
    mySerial.print("\t");                // Print a tab character
    mySerial.print(a, DEC);    // Print as an ASCII-encoded decimal
    mySerial.print("\t");                // Print a tab character
    mySerial.print(a, HEX);    // Print as an ASCII-encoded hexadecimal
    mySerial.print("\t");                // Print a tab character
    mySerial.print(a, OCT);    // Print as an ASCII-encoded octal
    mySerial.print("\t");                // Print a tab character
    mySerial.print(a, BIN);    // Print as an ASCII-encoded binary
    mySerial.print("\t");                // Print a tab character
    //mySerial.print(a/4, BYTE);
    */             
}

