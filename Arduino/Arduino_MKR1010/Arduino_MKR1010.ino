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

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2LxgUF6TY"
#define BLYNK_TEMPLATE_NAME "monvoltin"
#define BLYNK_AUTH_TOKEN "LHTtoPg_FZZ6VKBfSnSdlmv2BOYWWQZv"

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi9A";
char pass[] = "02021984";

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); 
}

void sendSensorData() {
  int voltage0 = analogRead(A0);
  int voltage1 = analogRead(A1);
  //float voltage=analogRead(A0)/100;
  delay(2000);
  Blynk.virtualWrite(V1, voltage0);
  delay(2000);
  Blynk.virtualWrite(V2, voltage1);
}

BLYNK_WRITE(V1){
  int pinValue = param.asInt();
}

BLYNK_WRITE(V2){
  int pinValue = param.asInt();
}

void loop()
{
  Blynk.run();
  sendSensorData();
}
