#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int LEDHot = 8;
int LEDCool = 9;
int BUZZER = 10;

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  pinMode(LEDHot, OUTPUT);
  pinMode(LEDCool, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  lcd.begin(16,2);
  startme();
}

void loop() {

  float temp = ReadTemp();

  if(temp > 29) {
    digitalWrite(LEDHot, HIGH);
    digitalWrite(LEDCool, LOW);
    if(temp > 30)
      startBuzzer();
  } else {
    digitalWrite(LEDHot, LOW);
    digitalWrite(LEDCool, HIGH);
    
  }
  
  lcd.clear();
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("Temp: "); 
  lcd.print(temp);
  lcd.print(" C"); 

  if(temp > 30) {
    lcd.setCursor(0,1);
    lcd.print("We're dying!!!");
  }

  delay(1000);
}

float ReadTemp() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  return T;
}

void startBuzzer() {
  for(int i=0; i<5; i++) {
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
  }

}

void startme() {
  startBuzzer();
  
  lcd.print("Loading...");
  for(int i = 0; i < 11; i++) {
    digitalWrite(LEDCool, HIGH);
    delay(70);
    digitalWrite(LEDCool,LOW);
    digitalWrite(LEDHot, HIGH);
    delay(70);
    digitalWrite(LEDHot, LOW);
}
}
