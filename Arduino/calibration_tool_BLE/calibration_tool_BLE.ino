/*
This program let sensor calibrations generating a digital reference. It will be compared with an sensorValue A0.
1. Use the App Calibration_Tool_BLE_1024 to generate a digital reference.
2. Set the reference.
3. Reset the IoT device and you must verify that pin12 is On if reference = sensorValue A0.
4. Disconnect App Calibration_Tool_BLE_1024 with Disconnect button.
*/

#include <ArduinoBLE.h>
#include <FlashStorage.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service
FlashStorage(stored_state_holder, uint16_t);

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEShortCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin=13,outputPin=12; // pin to use for the LED
int reference,sensorValue;
uint16_t systemState;
const int analogPin=A0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  pinMode(outputPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Calibration tool");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characteristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("Waiting for connections.");

  systemState=stored_state_holder.read();
  Serial.print("Current state recovered from Flash: ");
  Serial.println(systemState);
  reference=systemState;
  Serial.println("Reference: ");
  Serial.println(reference);
}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();  

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // Retrieve and print the local MAC/Device address
    String macAddress = BLE.address();  
   
    Serial.print("Arduino BLE MAC Address: ");
    Serial.println(macAddress);
    Serial.println("SensorValue: ");    
    Serial.println(sensorValue);    
    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {   // any value other than 0
          Serial.println("Data was received");          
          //Starting test.
          reference=switchCharacteristic.value();
          systemState=reference;
          stored_state_holder.write(systemState);
          Serial.println(reference);
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          delay(500);
          digitalWrite(ledPin, LOW);

        } else {                              // a 0 value
          Serial.println(F("Data 0 was received"));
          digitalWrite(outputPin,LOW);
          reference=switchCharacteristic.value();
          systemState=reference;
          stored_state_holder.write(systemState);
          Serial.println(reference);
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          delay(500);
          digitalWrite(ledPin, LOW);
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
  Serial.println("Monitoring"); //When I do the installation, I must delete the //.
  delay(1000);
  sensorValue=analogRead(analogPin);
  if (sensorValue>reference){
    Serial.println("Alert!");
    digitalWrite(outputPin,HIGH);
    digitalWrite(ledPin,HIGH);   
  } 
}
