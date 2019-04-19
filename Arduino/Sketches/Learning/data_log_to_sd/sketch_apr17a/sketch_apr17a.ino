#include "Card.h"
#include "Thermostat.h"

int SD_CARD_RESET_PIN = 4;
int LED_PIN = 7;

Card card;

void setup() {
  
  Serial.begin(9600);
  card.Initialise(SD_CARD_RESET_PIN, LED_PIN);
  card.CreateFile("text.txt");
  card.WriteToFile("Initialised 1");
  card.CloseFile();
  card.OpenFile("text.txt");
  card.CloseFile();
}
// Global variables.


void loop() {

   
}
