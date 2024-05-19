// Bluetooth HC-05
// L298M
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
    int Datonum = DATO - '0'; // Convertir char a entero

    if (DATO != 0){ // Verificar si está resiviendo un valor

    if(Datonum == 1 && Datonum == 2 ){
        digitalWrite(ENB, HIGH); // Habilitamos motor B
        digitalWrite(IN3, HIGH); // Configuramos segundo giro
        digitalWrite(IN4, LOW);  // **************************
   
        digitalWrite(ENA, HIGH); // Habilitamos motor A
        digitalWrite(IN1, HIGH); // Configuramos segundo giro
        digitalWrite(IN2, LOW);  // **************************
        
        delay(1); // motor prendido 
      }
    if(Datonum == 3 && Datonum == 4){
        digitalWrite(ENB, HIGH); // Habilitamos motor B
        digitalWrite(IN3, LOW); // Configuramos segundo giro
        digitalWrite(IN4, HIGH);  // **************************

        digitalWrite(ENA, HIGH); // Habilitamos motor A
        digitalWrite(IN1, LOW); // Configuramos segundo giro
        digitalWrite(IN2, HIGH);  // **************************
        delay(1); // motor prendido
      }
      
    switch (Datonum) {
      case 1:
        digitalWrite(ENB, HIGH); // Habilitamos motor B
        digitalWrite(IN3, HIGH); // Configuramos segundo giro
        digitalWrite(IN4, LOW);  // **************************
        digitalWrite(ENA, LOW);  // Apagamos motor A
        delay(1); // motor prendido
        break;

      case 2:
        digitalWrite(ENB, LOW);  // Apagamos motor B
        digitalWrite(ENA, HIGH); // Habilitamos motor A
        digitalWrite(IN1, HIGH); // Configuramos segundo giro
        digitalWrite(IN2, LOW);  // **************************
        delay(1); // motor prendido 
        break;

      case 3:
        digitalWrite(ENB, HIGH); // Habilitamos motor B
        digitalWrite(IN3, LOW); // Configuramos segundo giro
        digitalWrite(IN4, HIGH);  // **************************
        digitalWrite(ENA, LOW);  // Apagamos motor A
        delay(15); // motor prendido 
        break;

      case 4:
        digitalWrite(ENB, LOW);  // Apagamos motor B
        digitalWrite(ENA, HIGH); // Habilitamos motor A
        digitalWrite(IN1, LOW); // Configuramos segundo giro
        digitalWrite(IN2, HIGH);  // **************************
        delay(15); // motor prendido 
        break;

      default:
        // Apagar ambos motores si el dato no es reconocido
        digitalWrite(ENA, LOW);
        digitalWrite(ENB, LOW);
        break;
    }}

  }
}
