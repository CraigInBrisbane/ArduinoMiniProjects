#include "Card.h"
#include "Thermostat.h"

int SD_CARD_RESET_PIN = 4;
int LED_PIN = 7;
int TEMP_PIN = A3;

Card card;
Thermostat thermostat;

void setup() {
  
  Serial.begin(9600);
  card.Initialise(SD_CARD_RESET_PIN, LED_PIN);
  thermostat.Init(TEMP_PIN, 10000, 1000);
  card.CreateFile("TempData.log");
}
// Global variables.


void loop() {
  Serial.println("-----------------");
  long val = thermostat.Read();
  String logLine = "";
  logLine = logLine + millis();
  logLine = logLine + ",";
  logLine = logLine + val;
  card.OpenFile("TempData.log");
  card.WriteToFile(logLine);
  card.CloseFile();

  Serial.print("Thermostat.Read() returning ");
  Serial.println(val);
  delay(10000); 
}
