// helpful: https://learn.adafruit.com/multi-tasking-the-arduino-part-3/using-neopatterns

#include "Arduino.h"

#ifndef Animation_h
#define Animation_h

typedef void (*updateFunction)(unsigned long, unsigned long, int, int); // elapsed, duration, step, steps

class Animation
{
  public:
    Animation();
    void setAnimation(unsigned long duration, bool loopAnimation, updateFunction function, int steps);
    void update();
    bool alive;
    static int step(long elapsed_time, long duration, int value) {
      return (elapsed_time % duration) * value / duration;
    }
  private:
    updateFunction _update;
    unsigned long _start; //ms
    unsigned long _duration; //ms
    int _steps;
    int _lastStep;
    bool _loop;
};

void animate_indicator_left(unsigned long elapsed_time, unsigned long duration, int step, int steps);
void animate_indicator_right(unsigned long elapsed_time, unsigned long duration, int step, int steps);
void animate_indicator_warning(unsigned long elapsed_time, unsigned long duration, int step, int steps);
void animate_sirens(unsigned long elapsed_time, unsigned long duration, int step, int steps);


#endif
