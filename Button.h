#include "Arduino.h"

#ifndef Button_h
#define Button_h

// Button ----------------------
#define DEBOUNCE_DELAY 50  //ms
#define BUTTON_PIN 4
// -----------------------------


typedef void (*callbackFunction)();

class Button {
public:
  Button() {}

  void setCallback(callbackFunction callback) {
    _callback = callback;
  }

  void update() {
    int reading = digitalRead(BUTTON_PIN);
    if (reading != lastState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      if (reading != state) {
        state = reading;

        if (state == HIGH) {
          Serial.println("Button Released");
        } else {
          Serial.println("Button Pushed");
          if (_callback != NULL) {
            _callback();
          }
        }
      }
    }
    lastState = reading;
  }

private:
  callbackFunction _callback;
  int state;
  int lastState = HIGH;
  unsigned long lastDebounceTime = 0;
};

#endif