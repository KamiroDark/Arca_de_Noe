#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);             
  SerialBT.begin("ESP32_Bluetooth"); // Nombre BluetoothVisible
  Serial.println("Bluetooth iniciado. Busque 'ESP32_Bluetooth' para conectar.");
  // Iniciar UART2: RX en GPIO16, TX en GPIO17 (115200 baudios):contentReference[oaicite:14]{index=14}.
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  // Si llegan datos del Arduino por Serial2:
  if (Serial2.available()) {
    String dist = Serial2.readStringUntil('\n'); 
    // Mostrar en Monitor Serial
    Serial.println("Distancia: " + dist + " cm");
    // Enviar por Bluetooth clásico al dispositivo emparejado
    SerialBT.println(dist);
  }
}