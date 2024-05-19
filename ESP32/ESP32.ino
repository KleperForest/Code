#include "BluetoothSerial.h"

#define BUTTON_PIN 2 // Pin where the button is connected

BluetoothSerial SerialBT;
const char *pin = "1234"; // HC-05 PIN code
String slaveName = "MASTER_HC5_A"; // HC-05 device name
String myName = "ESP32-BT-Master";
bool buttonPressed = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure the button pin as input with pull-up resistor
  Serial.begin(38400);

  SerialBT.begin(myName, true); // Start Bluetooth in master mode
  Serial.printf("The device \"%s\" started in master mode, make sure slave BT device is on!\n", myName.c_str());

  // Attempt to connect to the HC-05
  SerialBT.setPin(pin);
  Serial.printf("Connecting to slave BT device named \"%s\"\n", slaveName.c_str());
  bool connected = SerialBT.connect(slaveName);

  if (connected) {
    Serial.println("Connected Successfully!");
  } else {
    while (!SerialBT.connected(38400)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!buttonPressed) {
      SerialBT.write('2');
      Serial.println("Sent '1' to HC-05");
      buttonPressed = true;
    }
  } else {
    buttonPressed = false;
  }

  delay(20);
}
