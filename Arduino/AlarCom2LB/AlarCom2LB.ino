/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino MKR 1010
  to connect your project to Blynk.

  NOTE: This requires WiFiNINA library

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
/* Fill in information from Blynk Device Info here */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"
//#define BLYNK_AUTH_TOKEN            "YourAuthToken"
#define BLYNK_TEMPLATE_ID "TMPL2HoGJbbU-"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "0fYh9dHks4prZzHRjLCOAt7k0wC4nIAJ"

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi 9A";
char pass[] = "Azul2284";

int cont=0,onoroff=0,sensorReading=0;
  
BLYNK_WRITE(V0){
  sensorReading = analogRead(0);
  Blynk.virtualWrite(V1,sensorReading);
  Serial.print(cont);
  //Serial.print(sensorReading);
  onoroff=cont%2;
  if (onoroff==0){
    digitalWrite(LED_BUILTIN,HIGH);
    digitalWrite(2,HIGH);    
  }
  else {
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(2,LOW);    
  }
  cont=cont+1;
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "https://blynk.cloud/dashboard/86082/templates/161833/dashboard", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,0,12), 8080);
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  pinMode(2, OUTPUT);      // set the LED pin mode
 }
 
void loop()
{  
  Blynk.run();
}
