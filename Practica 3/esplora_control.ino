#include <Esplora.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 11);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void activarFeedback() {

  Esplora.tone(1000, 100); 


  Esplora.writeRGB(0, 255, 0); 
}

void apagarLED() {
  Esplora.writeRGB(0, 0, 0); 
}

void loop() {
  int x = Esplora.readJoystickX();
  int y = Esplora.readJoystickY();

  bool accion = false; 

  if (y < -50) {
    mySerial.print('F');
    accion = true;
  }
  else if (y > 50) {
    mySerial.print('B');
    accion = true;
  }
  else if (x > 50) {
    mySerial.print('R');
    accion = true;
  }
  else if (x < -50) {
    mySerial.print('L');
    accion = true;
  }

  if (Esplora.readButton(SWITCH_2) == LOW) {
    mySerial.print('2');
    accion = true;
  }
  if (Esplora.readButton(SWITCH_1) == LOW) {
    mySerial.print('1');
    accion = true;
  }
  if (Esplora.readButton(SWITCH_3) == LOW) {
    mySerial.print('3');
    accion = true;
  }
  if (Esplora.readButton(SWITCH_4) == LOW) {
    mySerial.print('4');
    accion = true;
  }

  if (accion) {
    activarFeedback();
  } else {
    apagarLED();
  }

  delay(40);
}