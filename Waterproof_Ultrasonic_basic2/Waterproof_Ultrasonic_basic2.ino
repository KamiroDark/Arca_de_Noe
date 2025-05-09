const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup() {
  Serial.begin(9600);  // Comunicación serial con el PC
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Enviar pulso ultrasónico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Medir duración del eco
  long duracion = pulseIn(ECHO_PIN, HIGH, 25000);  // Timeout de 25ms
  float distancia = duracion * 0.034 / 2;  // Convertir a cm

  // Validar que esté dentro del rango típico del JSN-SR04M (20cm a 600cm)
  if (distancia >= 20 && distancia <= 600) {
    Serial.println(distancia, 2);  // Enviar solo el número con 2 decimales
  }

  delay(100);  // Esperar 0.5 segundos antes de la siguiente medición
}
