class Buzzer {
  int pin = 0;
  unsigned long lastMillis = 0;
  unsigned long toneTime = 0;
  int pitch = 0;
  bool isBuzzing = false;

  public:
  Buzzer(int Pin){
    pin = Pin;
    pinMode(pin, OUTPUT);
  }

  void Beep(int ToneTime) {
    Serial.println("Starting buzzer...");
    isBuzzing = true;
    toneTime = ToneTime;
    tone(pin, 2000);
    lastMillis = millis();
  }

  void Update() {
    unsigned long currentMillis = millis();
    
    if(isBuzzing && currentMillis - lastMillis > toneTime) {
      Serial.println("Stopping buzzer");
      noTone(pin);
      isBuzzing = false;
    }
  }

  
};
