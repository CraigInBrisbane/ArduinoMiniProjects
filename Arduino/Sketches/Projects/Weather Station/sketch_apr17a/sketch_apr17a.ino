#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include "Thermostat.h"

int OLED_RESET = 4; // Reset pin # (or -1 if sharing Arduino reset pin)
int THERMOSTAT_PIN = 0;

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void displayDetails(float temp, float minTemp, float maxTemp) {
  
  display.clearDisplay();
  display.setFont();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  String tempString = "T ";
  tempString+= temp;
  tempString+= " 'C";
  String humidity = "H 69.3 %";
  String pressure = "P 1080 hPa";

  display.setCursor(0,0);
  display.print(tempString);

  display.setTextSize(1);
  display.setCursor(0, 17);

  String maxs = "Max: ";
  maxs += maxTemp;
  maxs += " 'C";

  display.println(maxs);

  display.setCursor(0, 25);

  String mins = "Min: ";
  mins += minTemp;
  mins += " 'C";
  
  display.println(mins);
   
  
  /*
  display.setCursor(0,12);
  display.println(humidity);

  display.setCursor(0,24);
  display.println(pressure);

  display.setCursor(72,0);
  display.println("H 28.3 'C");
  
  display.setCursor(72,12);
  display.println("L 12.4 'C");
      
  display.setCursor(72,24);
  display.println("Rising");
*/
  display.display();

}

// Create the devices.
Thermostat thermostat(THERMOSTAT_PIN, 100000, 4000);

void setup() {
  
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setCursor(0,0);
  display.setFont();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Initialising...");
  display.display();
}

// Global variables.
unsigned long pauseTime = 1000;
unsigned long lastMillis = 0;
float maxTemp = -500;
float minTemp = 500;

void loop() {

  unsigned long currentMillis = millis();
  if(currentMillis - lastMillis > pauseTime) {
    float currentTemp = thermostat.Read();
    if(currentTemp > maxTemp) {
      maxTemp = currentTemp;
    }

    if(currentTemp < minTemp) {
      minTemp = currentTemp;
    }
    displayDetails(currentTemp, minTemp, maxTemp);
    lastMillis = millis();
    
  }
}
