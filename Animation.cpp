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
      _update(elapsed_time, _duration, step);
    }
  }
}

void animate_indicator_left(unsigned long elapsed_time, unsigned long duration, int step) {
  Serial.print("LEFT INDICATOR LED: ");
  Serial.println(step);

  // Front left LEDS 0-3, Rear left LEDS 12-15
  setColorLoop(0, 4, CRGB::Black);
  setColorLoop(12, 4, CRGB::Black);
  leds[step] = CRGB::Yellow;
  leds[step + 12] = CRGB::Yellow;
  FastLED.show();
}

void animate_indicator_right(unsigned long elapsed_time, unsigned long duration, int step) {
  Serial.print("RIGHT INDICATOR LED: ");
  Serial.println(INDICATOR_RIGHT_STEPS - step - 1);

  // Front right LEDS 4-7, Rear right LEDS 8-11
  setColorLoop(4, 8, CRGB::Black);
  leds[step + 4] = CRGB::Yellow;
  leds[step + 8] = CRGB::Yellow;
  FastLED.show();
}

void animate_indicator_warning(unsigned long elapsed_time, unsigned long duration, int step) {
  Serial.print("INDICATORS LED: ");
  Serial.println(step == 0);

  bool on = step % 2 == 1;
  CRGB color = on ? CRGB::Yellow : CRGB::Yellow;

  // LEDS 0-15
  setColorLoop(0, 15, color);
  FastLED.show();
}

void animate_sirens(unsigned long elapsed_time, unsigned long duration, int step) {
  Serial.print("SIRENS: ");

  // reset all
  setColorLoop(16, 12, CRGB::Black);

  if (step < 12) {
    if (step % 2 == 0) {
      if (step > 5) {
        // LEDS 16-21
        setColorLoop(22, 6, CRGB::Blue);
        Serial.println("RIGHT");
      } else {
        // LEDS 22-27
        setColorLoop(16, 6, CRGB::Red);
        Serial.println("LEFT");
      }
    } else {
      Serial.println("OFF");
    }
  } else {
    if (step % 2 == 0) {
      // LEDS 16-27
      setColorLoop(16, 5, CRGB::Blue);
      setColorLoop(21, 2, CRGB::White);
      setColorLoop(23, 5, CRGB::Red);
      Serial.println("BOTH");
    } else {
      Serial.println("OFF");
    }
  }

  FastLED.show();
}