#include "Arduino.h"
#include "Animation.h"
#include "Leds.h"
#include "Enums.h"

Animation::Animation() {
  _start = 0;
  _duration = 0;
  _steps = 0;
  _lastStep = -1;
  _loop = false;
  _alive = false;
}

void Animation::play(AnimationType animationType) {
  switch(animationType) {
    case ANIMATE_INDICATORS_LEFT: 
      setAnimation(1000, true, animate_indicator_left, INDICATOR_LEFT_STEPS);
      break;
    case ANIMATE_INDICATORS_RIGHT: 
      setAnimation(1000, true, animate_indicator_right, INDICATOR_RIGHT_STEPS);
      break;
    case ANIMATE_INDICATORS_WARNING: 
      setAnimation(1000, true, animate_indicator_warning, INDICATOR_WARNING_STEPS);
      break;
    case ANIMATE_SIRENS: 
      setAnimation(2000, true, animate_sirens, SIRENS_STEPS);
      break;
  }
}

void Animation::setAnimation(unsigned long duration, bool loopAnimation, updateFunction update, int steps) {
  _start = millis();
  _duration = duration;
  _steps = steps;
  _loop = loopAnimation;
  _update = update;
  _lastStep = -1;
  _alive = true;
}

void Animation::update() {
  if (_alive == false || _update == NULL) {
    return;
  }
  unsigned long elapsed_time = millis() - _start;

  if (elapsed_time >= _duration) {
    if (_loop) {
      _start = millis();
    } else {
      _alive = false;
    }
  } else {
    int step = Animation::step(elapsed_time, _duration, _steps);
    if (step != _lastStep) {
      _lastStep = step;
      _update(elapsed_time, _duration, step, false);
      FastLED.show();
    }
  }
}

void Animation::stop() {
  _alive = false;
  _update(0, 0, 0, true);
  FastLED.show();
}

void animate_indicator_left(unsigned long elapsed_time, unsigned long duration, int step, bool stop) {
  // Serial.print("LEFT INDICATOR LED: ");
  // Serial.println(step);

  // Front left LEDS 0-3, Rear left LEDS 12-15
  setColorLoop(0, 4, CRGB::Black);
  setColorLoop(12, 4, CRGB::Black);
  if(stop) return;

  if(step <= 4) {
    setColorLoop(0, step, CRGB::OrangeRed);
    setColorLoop(12, step, CRGB::OrangeRed);
  } else {
    setColorLoop(step % 4, 4 - step % 4 , CRGB::OrangeRed);
    setColorLoop(12 + step % 4, 4 - step % 4, CRGB::OrangeRed);
  }  
}

void animate_indicator_right(unsigned long elapsed_time, unsigned long duration, int step, bool stop) {
  // Serial.print("RIGHT INDICATOR LED: ");
  // Serial.println(INDICATOR_RIGHT_STEPS - step - 1);

  // Front right LEDS 4-7, Rear right LEDS 8-11
  setColorLoop(4, 8, CRGB::Black);
  if(stop) return;

  leds[step + 4] = CRGB::OrangeRed;
  leds[step + 8] = CRGB::OrangeRed;
}

void animate_indicator_warning(unsigned long elapsed_time, unsigned long duration, int step, bool stop) {
  // Serial.print("INDICATORS LED: ");
  // Serial.println(step % 2 == 1);

  if(stop) {
    setColorLoop(0, 15, CRGB::Black);
    return;
  }

  bool on = step % 2 == 1;
  CRGB color = on ? CRGB::OrangeRed : CRGB::Black;

  // LEDS 0-15
  setColorLoop(0, 15, color);
}

void animate_sirens(unsigned long elapsed_time, unsigned long duration, int step, bool stop) {
  // Serial.print("SIRENS: ");

  // reset all
  setColorLoop(16, 12, CRGB::Black);
  if(stop) return;

  if (step < 12) {
    if (step % 2 == 0) {
      if (step > 5) {
        // LEDS 16-21
        setColorLoop(22, 6, CRGB::Blue);
        // Serial.println("RIGHT");
      } else {
        // LEDS 22-27
        setColorLoop(16, 6, CRGB::Red);
        // Serial.println("LEFT");
      }
    } else {
      // Serial.println("OFF");
    }
  } else {
    if (step % 2 == 0) {
      // LEDS 16-27
      setColorLoop(16, 5, CRGB::Blue);
      setColorLoop(21, 2, CRGB::White);
      setColorLoop(23, 5, CRGB::Red);
      // Serial.println("BOTH");
    } else {
      // Serial.println("OFF");
    }
  }
}