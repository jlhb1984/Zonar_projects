int pin2=2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin2,HIGH);
  delay(10000);
  digitalWrite(pin2,LOW);
  delay(5000);
}
