// helpful: https://learn.adafruit.com/multi-tasking-the-arduino-part-3/using-neopatterns

#include "Arduino.h"
#include "Enums.h"

#ifndef Animation_h
#define Animation_h

#define INDICATOR_LEFT_STEPS 8
#define INDICATOR_RIGHT_STEPS 4
#define INDICATOR_WARNING_STEPS 2
#define SIRENS_STEPS 24

typedef void (*updateFunction)(unsigned long, unsigned long, int, bool); // elapsed, duration, step, stop

class Animation
{
  public:
    Animation();
    void play(AnimationType animationType);
    void update();
    void stop();
    static int step(long elapsed_time, long duration, int value) {
      return (elapsed_time % duration) * value / duration;
    }
  private:
    void setAnimation(unsigned long duration, bool loopAnimation, updateFunction function, int steps);
    updateFunction _update;
    unsigned long _start; //ms
    unsigned long _duration; //ms
    int _steps;
    int _lastStep;
    bool _loop;
    bool _alive;
};

void animate_indicator_left(unsigned long elapsed_time, unsigned long duration, int step, bool stop);
void animate_indicator_right(unsigned long elapsed_time, unsigned long duration, int step, bool stop);
void animate_indicator_warning(unsigned long elapsed_time, unsigned long duration, int step, bool stop);
void animate_sirens(unsigned long elapsed_time, unsigned long duration, int step, bool stop);


#endif
