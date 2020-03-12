#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 4
#define DHTTYPE DHT11   // DHT 11
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);
const int pResistor = A0; 
int value;  

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  display.display();
  display.clearDisplay();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds
 
  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  value = map(analogRead(pResistor), 0, 1023, 0, 100);
  Serial.println(" ");
  Serial.print("lichthelderheid: ");
  Serial.print(value);
  Serial.print("%");
  
  
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
 
  display.setCursor(0,0);        
  display.println("temperatuur:"); 
  display.setCursor(0,17);        
  display.print(t);
  display.println(" Celcius"); 


  display.setCursor(0,32);        
  display.println("helderheid:"); 
  display.setCursor(0,47);        
  display.print(value);       
  display.println("%"); 

  display.display();
  delay(3000);


  
}
