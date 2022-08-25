#include "Enums.h"

class Headlights {
public:
  void next() {
    Serial.print("LIGHTS ");

    switch (state) {
      case OFF:
        Serial.println("OFF");
        state = LED_LIGHT;
        off();
        break;
      case LED_LIGHT:
        Serial.println("LEDS");
        state = HALF;
        leds();
        break;
      case HALF:
        Serial.println("HALF");
        state = FULL;
        halfLight();
        break;
      case FULL:
        Serial.println("FULL");
        state = OFF;
        fullLight();
        break;
    }
  }

private:
  HeadlightState state = OFF;
  void off() {}
  void leds() {}
  void halfLight() {}
  void fullLight() {}
};