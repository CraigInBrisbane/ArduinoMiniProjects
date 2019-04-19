/*
 * A class to handle the reading of temperature data.
 */

class Thermostat {

  int ThermistorPin = 0;  // The pin this device will listen on.
  int Vo;                 // The voltage we read from the pin.
  int Period;             // The time to wait to calculate the average.
  float R1 = 100000;      // The resistance of the resistor used.
  float logR2, R2, T;     // Fields for temperature calculation
  float c1 = 1.009249522e-03, 
        c2 = 2.378405444e-04, 
        c3 = 2.019202697e-07; // No idea... Just values.

  public:
  Thermostat(int pin, float resistor, int period) {
    ThermistorPin = pin;
    R1 = resistor;
    Period = period;
    pinMode(ThermistorPin, OUTPUT);
  }


  int readCount = 0;
  float totalReadValue = 0;

  unsigned long startMillis = 0;

  /*
   * Read the value from the device.
   */
  float Read() {


    startMillis = millis();
    readCount = 0;
    totalReadValue = 0;
    while(millis() - startMillis < Period) {
      Serial.println("Checking voltage....");
      Vo = analogRead(ThermistorPin);
      R2 = R1 * (1023.0 / (float)Vo - 1.0);
      logR2 = log(R2);
      T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
      T = T - 273.15;

      readCount ++;
      totalReadValue = totalReadValue + T;
    }
    Serial.println("Returning..");
    Serial.println(totalReadValue);
    Serial.println(readCount);
    
    return totalReadValue / readCount;
  }
};
