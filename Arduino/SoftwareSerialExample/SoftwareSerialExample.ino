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
int s10,s11,s12,s13,s20,s21,s22,s23;

SoftwareSerial mySerial(10, 11,1); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
   // set the data rate for the SoftwareSerial port  
  mySerial.begin(9600);  
}

void loop() {
    s10=49; //hex=31
    mySerial.write(s10);
    delay(10);
    s11=1; //hex=01
    mySerial.write(s11);
    delay(10);
    s12=6; //hex=06
    mySerial.write(s12);
    delay(10);
    s13=108; //hex=6C
    mySerial.write(s13);
    delay(1000);
    s20=49; //hex=31
    mySerial.write(s20);
    delay(10);
    s21=2; //hex=01
    mySerial.write(s21);
    delay(10);
    s22=6; //hex=06
    mySerial.write(s22);
    
    delay(10);
    s23=57; //hex=6C
    mySerial.write(s23);
    delay(1000);
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

