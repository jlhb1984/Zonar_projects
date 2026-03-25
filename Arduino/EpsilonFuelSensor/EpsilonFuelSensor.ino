/*
  WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi module (once connected)
 to the Serial Monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.

 If the IP address of your board is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and Uno WiFi Rev.2)
 * LED attached to pin 9

 created 25 Nov 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Redmi9A";        // your network SSID (name)
char pass[] = "Azul1984*2025";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // initialize serial communication
  Serial1.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  pinMode(2, OUTPUT);      // set the LED pin mode



  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out to the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            int sensorReading = analogRead(0);
            client.print("Click <a href=\"/H\">en este enlace</a> para simular llenado.<br>");
            client.print("Click <a href=\"/L\">en este enlace</a> para simular vaciado.<br>");
            client.print("Click <a href=\"/B\">en este enlace</a> para actualizar la lectura analogica.<br>");
            client.print("Valor analogico: ");
            client.print(sensorReading);                       
             // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
          digitalWrite(2, HIGH);
          
          //HEADER1
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);

          //MSB

          //1Prefix.
          Serial1.write(06); //HEX=3E
          delay(1);
          
          //2Sender network address.
          Serial1.write(64); //HEX=01
          delay(1);

          //3Command code.
          Serial1.write(136);//HEX=07
          delay(1);

          //4Temperature.
          Serial1.write(52); //HEX=19
          delay(1);

          //LSB

          //5User value of fuel level 1
          Serial1.write(132); //HEX=0F
          delay(1);
          //6User value of fuel level 2
          Serial1.write(132); //HEX=0F
          delay(1);

          //7Technological value of fuel level 1
          Serial1.write(152);//HEX=C7
          delay(1);
          //8Technological value of fuel level 2
          Serial1.write(141); //HEX=40
          delay(1);

          //9CRC.
          Serial1.write(59); //HEX=62
          delay(1);

          //HEADER 2
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);

        }

        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
             //HEADER1
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);

          //MSB

          //1Prefix.
          Serial1.write(06); //HEX=3E
          delay(1);

          //2Sender network address.
          Serial1.write(64); //HEX=01
          delay(1);

          //3Command code.
          Serial1.write(136);//HEX=07
          delay(1);

          //4Temperature.
          Serial1.write(52); //HEX=19
          delay(1);

          //LSB

          //5User value of fuel level 1
          Serial1.write(192); //HEX=0F
          delay(1);
          //6User value of fuel level 2
          Serial1.write(192); //HEX=0F
          delay(1);

          //7Technological value of fuel level 1
          Serial1.write(152);//HEX=C7
          delay(1);
          //8Technological value of fuel level 2
          Serial1.write(141); //HEX=40
          delay(1);

          //9CRC.
          Serial1.write(59); //HEX=62
          delay(1);

          //HEADER 2
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);
          Serial1.write(192); //HEX
          delay(1);
        }                 
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
