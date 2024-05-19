#include "BluetoothSerial.h"

BluetoothSerial serialBT;
char Data;

void setup(){
  serialBT.begin("ESP32-BT");
  }

void loop(){
  if(serialBT.available())
    Data = serialBT.read();

  }
