#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

const String device_name = "ESP32-Arca-Slave";

void setup() {
  Serial.begin(115200);  // Depuración por USB (opcional)
  Serial1.begin(9600, SERIAL_8N1, 1, 0);  // UART con el Arduino: RX=GPIO16, TX=GPIO17
  SerialBT.begin(device_name);  // Iniciar Bluetooth
  Serial.println("Bluetooth iniciado como: " + device_name);
}

void loop() {
  // Leer línea desde Arduino (UART)
  if (Serial1.available()) {
    String dato = Serial1.readStringUntil('\n');
    dato.trim();  // Quitar espacios en blanco o saltos

    if (dato.length() > 0) {
      String mensaje = "Distancia: " + dato + " cm\n";
      SerialBT.print(mensaje);  // Enviar al PC por Bluetooth
      Serial.print(mensaje);    // Mostrar en el monitor serie
    }
  }

  // (Opcional) Reenviar datos desde Bluetooth hacia el Arduino
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial1.write(c);
    Serial.print(c);
  }

  delay(10);
}
