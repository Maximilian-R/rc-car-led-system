#include "Enums.h"
#include "Leds.h"

#ifndef Headlights_h
#define Headlights_h

class Headlights {
public:
  void next() {
    switch (state) {
      case OFF:
        state = LED_LIGHT;
        break;
      case LED_LIGHT:
        state = HALF;
        break;
      case HALF:
        state = FULL;
        break;
      case FULL:
        state = OFF;
        break;
    }

    setState();
  }
  void setState() {
    Serial.print("LIGHTS ");

    switch (state) {
      case OFF:
        Serial.println("OFF");
        off();
        break;
      case LED_LIGHT:
        Serial.println("LEDS");
        leds();
        break;
      case HALF:
        Serial.println("HALF");
        halfLight();
        break;
      case FULL:
        Serial.println("FULL");
        fullLight();
        break;
    }
  }

private:
  HeadlightState state = OFF;
  void off() {
    // Front Left: 0-3 Front Right 4-7
    setColorLoop(0, 8, CRGB::Black);
    FastLED.show();
  }
  void leds() {
    // Front Left: 0-3 Front Right 4-7
    setColorLoop(0, 8, CRGB::White);
    FastLED.show();
  }
  void halfLight() {}
  void fullLight() {}
};

#endif