/*
 * A class that handles a flashing LED.
 */
class FlashingLed {
  int ledPin;
  long onTime;
  long offTime;
  int state;
  unsigned long previousMillis;

  public:
  FlashingLed(int LedPin, long On, long Off) {
    ledPin = LedPin;
    onTime = On;
    offTime = Off;
    pinMode(LedPin, OUTPUT);
    state = LOW;
    previousMillis = 0;
  }

  void Update() {
    unsigned long currentMillis = millis();
    
    if((state == HIGH) and (currentMillis - previousMillis >= onTime)) {
      state = LOW;
      //Serial.print("Going Low");
      //Serial.println(state);
      previousMillis = currentMillis;
      digitalWrite(ledPin, state);
    } 
    else
    if((state==LOW) and (currentMillis - previousMillis >= offTime)) {
      //Serial.println("Going High");
      state = HIGH;
      //Serial.println(state);
      previousMillis = currentMillis;
      digitalWrite(ledPin, state);
    }
  }
};
