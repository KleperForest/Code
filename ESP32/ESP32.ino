#include <HardwareSerial.h>

HardwareSerial mySerial(2); // Use UART2 (pins 16 and 17)

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // Configura la velocidad de comunicación con el HC-05
  Serial.println("Enviando datos al Arduino Nano a través del HC-05");
}

void loop() {
  mySerial.println("Hola desde el ESP32");
  delay(1000); // Envía un mensaje cada segundo
}
