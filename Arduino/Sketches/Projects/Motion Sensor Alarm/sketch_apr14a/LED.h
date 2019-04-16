
class LED {
  int pin = 0;

  public:
  LED(int Pin){
    pin = Pin;
    pinMode(pin, OUTPUT);
  }

  void On(){
    digitalWrite(pin, HIGH);
  }

  void Off(){
    digitalWrite(pin, LOW);
    
  }
};
