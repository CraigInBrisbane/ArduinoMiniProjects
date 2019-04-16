#include "PirSensor.h"
#include "LED.h"
#include "Buzzer.h"
#include "FlashingLED.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Declarations
int RED_PIN = 9;
int GREEN_PIN = 11;
int BUZZER_PIN = 13;
int PIR_PIN = 2;
int OLED_RESET = 4; // Reset pin # (or -1 if sharing Arduino reset pin)


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Pallete - Where you assign names to colors you like
#define BACKCOLOR 0xFFFF // White
#define LINECOLOR 0x0000

// Instantiate the objects we'll be using.
PirSensor pir(PIR_PIN);
FlashingLed green(GREEN_PIN, 50, 3000);
LED red(RED_PIN);
Buzzer buzzer(BUZZER_PIN);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void drawBox(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
  display.drawLine(topLeftX, topLeftY, topLeftX, bottomRightY, WHITE);
  display.drawLine(bottomRightX, bottomRightY, bottomRightX, bottomRightY, WHITE);
  display.drawLine(bottomRightX, bottomRightY, topLeftX, bottomRightY, WHITE);
  display.drawLine(topLeftX, bottomRightY, topLeftX, topLeftY ,WHITE);
}

void ShowScreen(String state, int Movements, bool indicatorOn) {
   display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,2);
  display.println("Status:");
  display.setCursor(2,18);
  display.println("Movements:");

  display.setCursor(70, 2);
  display.println(state);

  display.setCursor(70, 18);
  display.println(Movements);

  if(indicatorOn==true) {
    display.drawCircle(120,15, 3, WHITE);
    Serial.println(WHITE);
  } else {
    display.drawCircle(120,15, 3, BACKCOLOR);  
    Serial.println(BACKCOLOR);  
  }

  display.display();
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  ShowScreen("OFF", 0, false);

}

// Variables used in the loops.
bool lastStateIsMovement = false;
int MovementCount = 0;
unsigned long pause = 500;
unsigned long lastMillis = 0;
bool isOn = true;
String statusText = "STILL";


void loop() {
  // Read the movement sensor
  bool movement = pir.Check();
  
  unsigned long currentMillis = millis();
  if(currentMillis - lastMillis > pause) {
    isOn = !isOn;
    lastMillis = millis();
    ShowScreen(statusText, MovementCount, isOn);
  }

  // Was there movement and has this changed?  
  if(movement && lastStateIsMovement == false)
  {
    // Enable the alarm for a period of time.
    buzzer.Beep(150);
    MovementCount += 1;
    statusText= "ACTIVE";
  ShowScreen(statusText, MovementCount, isOn);
  } else 
  if(!movement && lastStateIsMovement) {
    statusText = "STILL";
  ShowScreen(statusText, MovementCount, isOn);
  }

  // Update the state of the last known state.
  lastStateIsMovement = movement;
  
  if(movement) {
    red.On();
  }
  else
  {
    red.Off();
  }
  green.Update();
  buzzer.Update();
  
}
