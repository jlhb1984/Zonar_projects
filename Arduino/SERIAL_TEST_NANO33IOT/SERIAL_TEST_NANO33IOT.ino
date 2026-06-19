void setup() {
  // initialize both serial ports:
  Serial.begin(2400);
  Serial1.begin(2400);
}

void loop() {
 
  /*
  for (int i=0; i<256; i++){ 
  Serial1.write(i);
  delay(1000);
  }
  */

  //Prefix.
  Serial1.write(06); //HEX=3E
  delay(10);

  //Sender network address.
  Serial1.write(64); //HEX=01
  delay(10);

  //Command code.
  Serial1.write(136);//HEX=07
  delay(10);

  //Temperature.
  Serial1.write(52); //HEX=19
  delay(2000);

  //User value of fuel level 1
  Serial1.write(58); //HEX=0C
  delay(10);
  //User value of fuel level 2
  Serial1.write(96); //HEX=04
  delay(10);

  //Technological value of fuel level 1
  Serial1.write(152);//HEX=C7
  delay(10);
  //Technological value of fuel level 2
  Serial1.write(141); //HEX=40
  delay(2000);

  //CRC.
  Serial1.write(59); //HEX=62
  delay(2000);

  /*
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(49);
  }
  */
}