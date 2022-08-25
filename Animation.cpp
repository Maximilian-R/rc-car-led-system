#include "Arduino.h"
#include "Animation.h"

Animation::Animation()
{
  _start = 0;
  _duration = 0;
  _steps = 0;
  _lastStep = -1;
  _loop = false;
  alive = false;
}

void Animation::setAnimation(unsigned long duration, bool loopAnimation, updateFunction update, int steps)
{
  _start = millis();
  _duration = duration;
  _steps = steps;
  _loop = loopAnimation;
  _update = update;
  _lastStep = -1;
  alive = true;
}

void Animation::update()
{
  if(alive == false || _update == NULL) {
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
    if(step != _lastStep) {
      _lastStep = step;
      _update(elapsed_time, _duration, step, _steps);
    }
  }
}

/*
0ms * 2 / 1000ms = 0
500ms * 2 / 1000ms = 1
1000ms * 2 / 1000ms = 2

0ms * 10 / 1000ms = 0
500ms * 10 / 1000ms = 5
1000ms * 2 / 1000ms = 10

time = elapsed time. If this can "overflow", do (time % duration)
*/
// int getStep(long elapsed_time, long duration, int value)
// {
//   return elapsed_time * value / duration;
// }


// 4 * 2 leds, 4 steps
void animate_indicator_left(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("LEFT INDICATOR LED: ");
  Serial.println(step);
}

// 4 leds * 2, 4 steps
void animate_indicator_right(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("RIGHT INDICATOR LED: ");
  Serial.println(steps - step - 1);
}

// 4 * 2 * 2, 2 steps
void animate_indicator_warning(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("INDICATORS LED: ");
  Serial.println(step == 0);
}

// 8 leds, 12 steps
void animate_sirens(unsigned long elapsed_time, unsigned long duration, int step, int steps) {
  Serial.print("SIRENS: ");
  // reset all lights in siren

  if(step % 2 == 0) {
    if (step > 5) {
      // right lights on
       Serial.println("RIGHT");
    } else {
      // left lights on
       Serial.println("LEFT");
    }
  } else {
    Serial.println("OFF");
  }
}


