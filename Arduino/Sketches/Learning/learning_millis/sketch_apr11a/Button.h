/*
 * A class to enable debounce on a button press, and return the state.
 */

class Button {
  int pin = 0;                        // The pin on which the button is connected.
  int lastButtonState = LOW;          // The last known button state since the last cycle.
  unsigned long lastDebounceTime = 0; // The last time a debounce was triggered.
  unsigned long delayTime = 20;       // How long we wait until we accept the value.

  public:
  Button(int Pin) {
    pin = Pin;
    pinMode(pin, INPUT);
  }

  bool Update() {
    // Read the pin.
    int result = digitalRead(pin);            

    // Has the result changed since we last checked?
    if(result != lastButtonState) {
      // If so, we set the debounce timer to now... and will check it when the delay has expired.
      lastDebounceTime = millis();
    }

    // Store the current state as the last known state...
    lastButtonState = result;

    // Now, has the delay time elapsed since the last change?
    if(millis() - lastDebounceTime > delayTime) {
      // If so, send the result.
      return result == HIGH;
    }

  }
};
