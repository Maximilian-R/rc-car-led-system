#include <FastLED.h>

#ifndef Leds_h
#define Leds_h

// LEDS -------------------------
#define LED_STRIP WS2812B
#define NUM_LEDS 144
#define LED_PIN 6
#define VOLTS 5
#define MAX_AMPS 500
// ------------------------------

extern CRGB leds[NUM_LEDS];

void setupLEDS();
void setColorLoop(int offset, int count, CRGB color);

#endif