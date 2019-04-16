/*
 * A class that manages a fading LED. This needs to be on PWM pin.
 */
class FadingLed {
  int             delayedStart = 0;               // Period to wait before starting. 
  int             ledPin = -1;                    // The pin to control
  long            fadePeriod = 0;                 // The time to do a full light and dim cycle. 
  unsigned long   previousMillis = 0;             // The previous millis value.
  bool            debug = false;                  // Should we output stuff?
  float           fadeChangeGap = 0;              // Calculated gap between brightness changes.
  
public:  
  FadingLed(int LedPin, int FadePeriod, int DelayedStart, bool Debug) {
    pinMode(ledPin, OUTPUT);
    ledPin = LedPin;
    fadePeriod = FadePeriod;
    delayedStart = DelayedStart;
    previousMillis = 0;  
    debug = Debug;    
  }

  void Update(bool isOn) {
      unsigned long currentMillis = millis();
      // Check if we have a delay set. If so, don't light up yet.
      if(delayedStart > currentMillis) {
        previousMillis = currentMillis;
        return;
      }
      
      // Map the difference which is betweem 0 and the cycle time, to a value between 0 and 512.
      int b = map(currentMillis - previousMillis, 0, fadePeriod, 0, 512); // 512, as we'll brighten to 256, then then fade from 256 to 512.
      int brightness = 0;

      // Check if we should be bringtning, or fading...
      if(b > 255) {
        brightness = 255 - (b-255);
      }
      else
      {
        brightness = b;
      }
      
      if(isOn == false) {
        brightness = 0;
      }  

      // Set the brightness.
      analogWrite(ledPin, brightness);

      // And then save the timestamp.
      if(currentMillis - previousMillis >= fadePeriod) {
         previousMillis = currentMillis;     
      }
      
    //}
  }
};
