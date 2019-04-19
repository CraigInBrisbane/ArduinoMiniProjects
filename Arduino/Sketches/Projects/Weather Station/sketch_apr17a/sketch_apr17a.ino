//#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

#include "Thermostat.h"

int OLED_RESET = 4; // Reset pin # (or -1 if sharing Arduino reset pin)
int THERMOSTAT_PIN = 0;

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int CS_PIN = 4;

// File file;

void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}

int openFile(char filename[])
{
  file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return 1;
  } else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}

int createFile(String filename)
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}


int writeToFile(String text)
{
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
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
Thermostat thermostat(THERMOSTAT_PIN, 10000, 5000);

void setup() {
  
  Serial.begin(9600);
  initializeSD();

  createFile("text.txt");
  writeToFile("Initialised");
  closeFile();
   
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
float maxTemp = -500;
float minTemp = 500;

void loop() {

  delay(1000);
//  Serial.println(analogRead(THERMOSTAT_PIN));
  float currentTemp = thermostat.Read();
 
  if(currentTemp > maxTemp) {
    maxTemp = currentTemp;
  }

  if(currentTemp < minTemp) {
    minTemp = currentTemp;
  }
  Serial.println(currentTemp);
  displayDetails(currentTemp, minTemp, maxTemp);
   
}
