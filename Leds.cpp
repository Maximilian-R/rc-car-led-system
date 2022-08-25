#include "Leds.h"
#include <FastLED.h>

CRGB leds[NUM_LEDS];

void setupLEDS() {
  FastLED.addLeds<LED_STRIP, LED_PIN>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
}