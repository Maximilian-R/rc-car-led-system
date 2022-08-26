// https://www.youtube.com/watch?v=PM4hES6rDJY&ab_channel=HAZITECH

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

/*  

...............LEFT.|.RIGHT...............
--------------------|---------------------
Front           0-3 | Front           4-7
--------------------|---------------------
Roof          16-21 | Roof          22-27
--------------------|---------------------
Rear          12-15 | Rear           8-11
--------------------|---------------------


...............LEFT.|.RIGHT...............
--------------------|---------------------
Bumber            0 | Bumper            9
Front           1-4 | Front           5-8
--------------------|---------------------
Interior         11 | Interior         10
--------------------|---------------------
Roof          12-17 | Roof          18-23
--------------------|---------------------
Bumber           29 | Bumper           28
Rear          30-33 | Rear          24-27
--------------------|---------------------

*/

extern CRGB leds[NUM_LEDS];

void setupLEDS();
void setColorLoop(int offset, int count, CRGB color);

#endif