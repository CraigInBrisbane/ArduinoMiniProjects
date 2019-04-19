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
  void Init(int LedPin, long On, long Off) {
    Serial.print("Executing led.Init()... pin is ");
    Serial.println(LedPin);
    ledPin = LedPin;
    onTime = On;
    offTime = Off;
    pinMode(LedPin, OUTPUT);
    previousMillis = 0;
    Serial.println("LED Initialised");
  }

  void Update() {
    unsigned long currentMillis = millis();
    
    if((state == HIGH) and (currentMillis - previousMillis >= onTime)) {
      state = LOW;
      previousMillis = currentMillis;
      digitalWrite(ledPin, state);
    } 
    else
    if((state==LOW) and (currentMillis - previousMillis >= offTime)) {
      state = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, state);
    }
  }

  void On() {
    Serial.println("Led -> On");
    digitalWrite(ledPin, HIGH);
  }

  void Off() {
    Serial.println("Led -> Off");
    digitalWrite(ledPin, LOW);
  }
};
