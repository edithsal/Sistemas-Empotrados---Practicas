#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>

#define RST 15
#define CE 2
#define DC 4
#define DIN 23
#define CLK 18

#define DHTPIN 21
#define DHTTYPE DHT11

#define BUZZER 22

#define LED_VERDE 18
#define LED_AMARILLO 22
#define LED_ROJO 5

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);
DHT dht(DHTPIN, DHTTYPE);

const int canal = 0;
const int resolucion = 8;

void setup() {
  Serial.begin(115200);

  display.begin();
  display.setContrast(40);
  dht.begin();

  ledcSetup(canal, 1000, resolucion);
  ledcAttachPin(BUZZER, canal);

  // LEDs
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);

  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(10, 16);
  display.println("Iniciando...");
  display.display();

  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  display.clearDisplay();
  display.setTextSize(1);

  if (isnan(temp) || isnan(hum)) {
    display.setCursor(0, 0);
    display.println("Error DHT11");
  } else {

    Serial.print("Temperatura: "); Serial.print(temp, 1); Serial.println(" C");
    Serial.print("Humedad:     "); Serial.print(hum, 0);  Serial.println(" %");

    display.setCursor(0, 0);
    display.println("Temperatura:");
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.print(temp, 1);
    display.println(" C");

    display.setTextSize(1);
    display.setCursor(0, 32);
    display.println("Humedad:");
    display.setCursor(50, 32);
    display.print(hum, 0);
    display.println("%");

    // LEDS 
    if (temp < 28) {
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO, LOW);

    } else if (temp >= 28 && temp <= 30) {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_ROJO, LOW);

    } else {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO, HIGH);
    }

    if (temp > 30) {
      ledcWriteTone(canal, 1800);
      delay(120);
      ledcWriteTone(canal, 0);
      delay(80);

      ledcWriteTone(canal, 1800);
      delay(120);
      ledcWriteTone(canal, 0);

      delay(600);
    } else {
      ledcWriteTone(canal, 0);
    }
  }

  display.display();
  delay(2000);
}