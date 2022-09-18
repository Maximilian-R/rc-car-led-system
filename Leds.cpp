#include "Leds.h"
#include <FastLED.h>

CRGB leds[NUM_LEDS];

void setupLEDS() {
  FastLED.addLeds<LED_STRIP, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
  // FastLED.setBrightness(5);
}

void setColorLoop(int offset, int count, CRGB color) {
  for (int i = offset; i < offset + count; i++) {
    leds[i] = color;
  }
}