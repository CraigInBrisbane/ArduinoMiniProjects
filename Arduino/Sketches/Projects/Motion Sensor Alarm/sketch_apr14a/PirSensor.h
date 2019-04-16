class PirSensor {
  int pin = 0;
  
   public:
  PirSensor(int Pin) {
    pin = Pin;
    pinMode(pin, INPUT);
  }

  bool Check() {
    int newState = digitalRead(pin);
    return newState == HIGH;
  }
};
