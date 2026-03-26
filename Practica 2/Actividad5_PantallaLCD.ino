#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Keypad.h>

// PINES
#define RST 15
#define CE 2
#define DC 4
#define DIN 16 //en el esp32 es RX2
#define CLK 17 //en el esp32 es TX2

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);


const byte rowsCount = 4;
const byte columsCount = 3;

char keys[rowsCount][columsCount] = {
  { '1','2','3' },
  { '4','5','6' },
  { '7','8','9' },
  { 'D','0','S' }
};

byte rowPins[rowsCount] = { 13, 12, 14, 27 };
byte columnPins[columsCount] = { 26, 25, 33 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

void setup() {

  display.begin();
  display.setContrast(50);

  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(BLACK);

  display.setCursor(0,0);
  display.println("HOLA");

  display.setCursor(24, 24);
  display.println("MUNDO");

  display.display();
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    display.clearDisplay();   

    display.setCursor(30,20); 
    display.setTextSize(3);   
    display.println(key);     
    display.display();        
  }

}