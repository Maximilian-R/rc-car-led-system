#include "Arduino.h"
#include "Animation.h"
#include "Leds.h"

Animation::Animation() {
  _start = 0;
  _duration = 0;
  _steps = 0;
  _lastStep = -1;
  _loop = false;
  alive = false;
}

void Animation::setAnimation(unsigned long duration, bool loopAnimation, updateFunction update, int steps) {
  _start = millis();
  _duration = duration;
  _steps = steps;
  _loop = loopAnimation;
  _update = update;
  _lastStep = -1;
  alive = true;
}

void Animation::update() {
  if (alive == false || _update == NULL) {
    return;
  }
  unsigned long elapsed_time = millis() - _start;

  if (elapsed_time >= _duration) {
    if (_loop) {
      _start = millis();
    } else {
      alive = false;
    }
  } else {
    int step = Animation::step(elapsed_time, _duration, _steps);
    if (step != _lastStep) {
      _lastStep = step;
      _update(elapsed_time, _duration, step, _steps);
    }
  }
}

// 4 * 2 leds, 4 steps
void animate_indicator_left(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("LEFT INDICATOR LED: ");
  Serial.println(step);

  // Front left LEDS 0-3, Rear left LEDS 12-15
  setColorLoop(0, 4, CRGB::Black);
  setColorLoop(12, 4, CRGB::Black);
  leds[step] = CRGB::Yellow;
  leds[step + 12] = CRGB::Yellow;
  FastLED.show();
}

// 4 leds * 2, 4 steps
void animate_indicator_right(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("RIGHT INDICATOR LED: ");
  Serial.println(steps - step - 1);

  // Front right LEDS 4-7, Rear right LEDS 8-11
  setColorLoop(4, 8, CRGB::Black);
  leds[step + 4] = CRGB::Yellow;
  leds[step + 8] = CRGB::Yellow;
  FastLED.show();
}

// 4 * 2 * 2, 2 steps
void animate_indicator_warning(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("INDICATORS LED: ");
  Serial.println(step == 0);

  bool on = step % 2 == 1;
  CRGB color = on ? CRGB::Yellow : CRGB::Yellow;

  // LEDS 0-15
  setColorLoop(0, 15, color);
  FastLED.show();
}

// 8 leds, 12 steps
void animate_sirens(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("SIRENS: ");

  // reset all
  setColorLoop(0, 16, CRGB::Black);

  if (step % 2 == 0) {
    if (step > 5) {
      setColorLoop(4, 8, CRGB::Blue);
      Serial.println("RIGHT");
    } else {
      setColorLoop(0, 4, CRGB::Red);
      setColorLoop(12, 4, CRGB::Red);
      Serial.println("LEFT");
    }
  } else {
    Serial.println("OFF");
  }
  FastLED.show();
}