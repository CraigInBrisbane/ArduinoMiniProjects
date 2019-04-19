/*
 * A class to handle the reading of temperature data.
 */

class Thermostat {

  int ThermistorPin = 0;  // The pin this device will listen on.
  float Vo;                 // The voltage we read from the pin.
  float R1 = 10000;      // The resistance of the resistor used.
  float logR2, R2, T;     // Fields for temperature calculation
  float c1 = 1.009249522e-03, 
        c2 = 2.378405444e-04, 
        c3 = 2.019202697e-07; // No idea... Just values.
  unsigned long readGap = 800; // Number of milliseconds between reads.
  unsigned long SamplePeriod;   // The time between sample value returns.


  public:
  void Init(int pin, float resistor, unsigned long samplePeriod) {
    Serial.print("Thermostat initialising on pin ");
    Serial.println(pin);
    ThermistorPin = pin;
    R1 = resistor;
    SamplePeriod = samplePeriod;
    pinMode(ThermistorPin, INPUT);
  }

  int readCount = 0;
  float totalReadValue = 0;
  unsigned long lastReadMillis = 0;
  unsigned long lastSampleMillis = 0;
  float lastReturnedTemp = 0;
  /*
   * Read the value from the device.
   */
  float Read() {
      Vo = analogRead(ThermistorPin);
      Serial.print("Voltage off thermostat: ");
      Serial.print(Vo);
      Serial.print(", with resistor value of ");
      Serial.print(R1);
      Serial.print(", on pin ");
      Serial.println(ThermistorPin);
      
      R2 = R1 * (1023.0 / (float)Vo - 1.0);
      logR2 = log(R2);
      T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
      T = T - 273.15;
  
      return T;
  }
};
