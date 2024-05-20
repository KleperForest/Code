#include <SoftwareSerial.h>

SoftwareSerial miBT(11, 10); // PINES RX Y TX

char DATO = 0; // Char comunicador

int IN1 = 5;  // Pin de control 1 motor A
int IN2 = 4;  // Pin de control 2 motor A
int ENA = 3;  // ON/OFF Motor A

int IN3 = 6;  // Pin de control 1 motor B
int IN4 = 7;  // Pin de control 2 motor B
int ENB = 9;  // ON/OFF Motor B

void setup() {
  // Velocidad de Modulo Bluetooth
  miBT.begin(38400);
  Serial.begin(38400);

  // Asignar como salida todos los pines al L298N
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  if (miBT.available()) { // LEE BT y envia a Arduino
    DATO = miBT.read();
    Serial.write(DATO);
    
    // Interpretar el byte recibido
    if (DATO & 0x01) { // Bit 0: Botón 1
      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else {
      digitalWrite(ENB, LOW);
    }
    
    if (DATO & 0x02) { // Bit 1: Botón 2
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else {
      digitalWrite(ENA, LOW);
    }

    if (DATO & 0x04) { // Bit 2: Botón 3
      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (!(DATO & 0x01)) { // Asegurar que el motor B se apague si el botón 1 tampoco está presionado
      digitalWrite(ENB, LOW);
    }

    if (DATO & 0x08) { // Bit 3: Botón 4
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else if (!(DATO & 0x02)) { // Asegurar que el motor A se apague si el botón 2 tampoco está presionado
      digitalWrite(ENA, LOW);
    }
  }
}
