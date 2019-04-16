#include "SPI.h"
#include "MFRC522.h"

// Assign the rfid pins.
#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8

// Assign the LED pins.
#define LED_GREEN A1
#define LED_RED A0
#define BUZZER_PIN 3

// No idea what this is.
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;


    String validIds[3] = { 
      "66:C5:04:1A", 
      "DB:9C:51:E8", 
      "24:14:EA:53" 
     };


void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  // Set the pin modes of the LEDs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // set the pin for the buzzer
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  
  if (!rfid.PICC_IsNewCardPresent()) // Is there no new card present?
    return;

  if (!rfid.PICC_ReadCardSerial()) { // Read the card. If we can't, bail.
    return;
  }

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("Your tag is not of type MIFARE Classic."));
      return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) { // Read in the first 4 bytes...
    strID +=                     // Add the byte to the string.    
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }

  if(validateCard(strID)) {
    digitalWrite(LED_GREEN, HIGH);
    tone(BUZZER_PIN, 3000);
    delay(100);
    noTone(BUZZER_PIN);
    delay(400);
  } else {
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(100);
    tone(BUZZER_PIN, 500);
    delay(400);
    noTone(BUZZER_PIN);
  }

  // Switch off the LEDs
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  // Stop reading.
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}


bool validateCard(String rfid) {

    rfid.toUpperCase();
    Serial.println("Validating " + rfid);
    
    for(int i = 0; i < sizeof(validIds); i++) {
      Serial.println("Checking " + validIds[i]);
      if(validIds[i] == rfid) {
        Serial.println("Valid!");
        return true;
      }
    }
    Serial.println("Invalid");
    return false;
}
