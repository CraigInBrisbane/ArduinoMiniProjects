#include "FadingLed.h"
#include "FlashingLed.h"
#include "Button.h"

FadingLed     led1(3,  400, 0, false);
FadingLed     led2(5,  400, 50, false);
FadingLed     led3(6,  400, 100, false);  
FadingLed     led4(9,  400, 150, false);
FadingLed     led5(10, 400, 200, false);
FadingLed     led6(11, 400, 250, false);
Button        button1(2);


void setup() {
  Serial.begin(115200);
}

void loop() {

  bool isOn = !button1.Update(); 
  
  led1.Update(true);
  led2.Update(isOn);
  led3.Update(isOn);
  led4.Update(isOn);
  led5.Update(isOn);
  led6.Update(isOn);
 }
