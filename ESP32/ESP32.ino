#include "BluetoothSerial.h"

const int B_1 = 4;   // B de boton
const int LED1 = 5;   
const int B_2 = 17;   
const int LED2 = 18;   
const int B_3 = 22;   
const int LED3 = 19;   
const int B_4 = 23;   
const int LED4 = 21; 

BluetoothSerial SerialBT;
const char *pin = "1234"; // HC-05 PIN code
String slaveName = "MASTER_HC5_A"; // HC-05 device name
String myName = "ESP32-BT-Master";
bool buttonPressed = false;

void setup() {
  // Configuración del pin del botón como entrada con pull-up interno
  pinMode(B_1, INPUT_PULLUP);
  pinMode(B_2, INPUT_PULLUP);
  pinMode(B_3, INPUT_PULLUP);
  pinMode(B_4, INPUT_PULLUP);
  
  // Configuración del pin del LED como salida
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  // Asegurarse de que el LED esté apagado inicialmente
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  Serial.begin(38400);

  // Comunicacion

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

  // Leer el estado de los botones y formar un byte para enviar
  byte buttonState = 0;
  
  if (digitalRead(B_1) == LOW) {
    buttonState |= 0x01; // Bit 0
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }

  if (digitalRead(B_2) == LOW) {
    buttonState |= 0x04; // Bit 1 //0x04
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }                                                                                                                                                                                                                                                                                                                                                                              

  if (digitalRead(B_3) == LOW) {
    buttonState |= 0x08; // Bit 2//0x08
    digitalWrite(LED3, HIGH);
  } else {
    digitalWrite(LED3, LOW);
  }

  if (digitalRead(B_4) == LOW) {
    buttonState |= 0x02; // Bit 3//0x02
    digitalWrite(LED4, HIGH);
  } else {
    digitalWrite(LED4, LOW);
  }

  // Enviar el estado de los botones
  SerialBT.write(buttonState);
  delay(50); // Pequeña demora para debouncing
}
