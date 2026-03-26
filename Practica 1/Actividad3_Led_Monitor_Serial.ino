void setup() {

  Serial.begin(115200);

  
  ledcSetup(0, 5000, 8);
  ledcAttachPin(32, 0);   

}

void loop() {

  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');
    input.trim();

    int brillo = input.toInt();

    if (brillo >= 0 && brillo <= 255) {
      ledcWrite(0, brillo);   
    } else {
      Serial.println("Valores fuera del rango (0-255)");
    }
  }
}
