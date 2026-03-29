const int ledPin = 32;

const int canal = 0;
const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcSetup(canal, freq, resolution); // Configura el canal
  ledcAttachPin(ledPin, canal);       // Asocia el pin al canal
}

void loop() {
  ledcWrite(canal, 128); // 50% brillo (0-255)
}