#include <avr/io.h>
#include <avr/interrupt.h>
/*
The program starts with clock signal defined by OCR1A registrer placed on void setup(). To turn off the clock, follow 
this options: x+6+cad.
*/
int val,apin0=A0,apin1=A1,apin2=A2,apin3=A3,apin4=A4,apin5=A5,dpin2=2,dpin13=13,dpin9=9,compin0=6,compin1=7;
char op,clock_op;

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
  Serial.print("0 CAD0, 1 CAD1, 2 CAD2, 3 CAD3, 4 CAD4, 5 CAD5 6 CLOCK OFF");
  
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

    default:
      Serial.print(" Fin");    
      }// del switch.  
 
}// del serialEvent
