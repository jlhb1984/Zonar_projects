void setup() {
  // initialize both serial ports:
  Serial.begin(2400);
  Serial1.begin(2400);
}

void loop() {
 
  
  for (int i=0; i<256; i++){ 
  Serial1.write(i);
  delay(10);
  }  
  
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