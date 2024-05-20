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
    } else if (!(DATO & 0x04)) { // Asegurar que el motor B se apague si el botón 3 tampoco está presionado
      digitalWrite(ENB, LOW);
    }
    
    if (DATO & 0x02) { // Bit 1: Botón 2
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else if (!(DATO & 0x08)) { // Asegurar que el motor A se apague si el botón 4 tampoco está presionado
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

    // Combinaciones de botones
    if ((DATO & 0x03) == 0x03) { // Botones 1 y 2
      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else if ((DATO & 0x05) == 0x05) { // Botones 1 y 3
      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else if ((DATO & 0x06) == 0x06) { // Botones 2 y 3
      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else if ((DATO & 0x09) == 0x09) { // Botones 1, 2 y 3
      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else {
      // Apagar ambos motores si ninguna combinación de botones está activa
      digitalWrite(ENA, LOW);
      digitalWrite(ENB, LOW);
    }
  }
}
