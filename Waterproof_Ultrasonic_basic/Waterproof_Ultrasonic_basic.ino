#include "Waterproof_Ultrasonic.h"

// Conexiones del sensor: Trig = pin 2, Echo = pin 3, Modo 1
Waterproof_Ultrasonic Waterproof_Ultrasonic(2, 3, 1);

void setup() {
  Serial.begin(9600);  // Comunicación UART hacia el ESP32
  delay(1000);         // Espera breve para estabilizar
}

void loop() {
  int distancia = Waterproof_Ultrasonic.ping_cm();  // Leer distancia en cm
  Serial.println(distancia);  // Enviar solo el número al ESP32

  delay(500);  // Espera medio segundo antes del siguiente envío
}
