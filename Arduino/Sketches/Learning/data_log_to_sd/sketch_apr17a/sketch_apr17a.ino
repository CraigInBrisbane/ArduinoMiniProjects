#include "Card.h"

int SD_CARD_RESET_PIN = 4;


Card card(SD_CARD_RESET_PIN);

void setup() {
  
  Serial.begin(9600);
  card.Initialise();
  card.CreateFile("text.txt");
  card.WriteToFile("Initialised 1");
  card.CloseFile();
  card.OpenFile("text.txt");
  card.CloseFile();
}
// Global variables.


void loop() {

   
}
