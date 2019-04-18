#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

int OLED_RESET = 4; // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Pallete - Where you assign names to colors you like
#define BACKCOLOR 0xFFFF // White
#define LINECOLOR 0x0000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ThermistorPin = 0;
int Vo;
float R1 = 100000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

float readTemperature() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  return T;
}

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
  display.println(tempString);

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

void setup() {
  // put your setup code here, to run once:
 
  pinMode(ThermistorPin, OUTPUT);
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

unsigned long pauseTime = 3000;
unsigned long lastMillis = 0;
float maxTemp = -500;
float minTemp = 500;

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if(currentMillis - lastMillis > pauseTime) {
    float currentTemp = readTemperature();
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
