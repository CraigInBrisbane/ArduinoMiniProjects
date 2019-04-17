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


void setup() {
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  String temp = "T 28.3 ";
  temp += (char)223;
  temp += "c";

 String humidity = "H 69.3% ";

  display.setCursor(0,12);
  display.println(temp);
  
  display.setCursor(0,31);
  display.println(humidity);
    
  display.display();

}

void loop() {
  // put your main code here, to run repeatedly:

}
