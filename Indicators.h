#include "Controller.h"
#include "Enums.h"
#include "Animation.h"

#ifndef Indicators_h
#define Indicators_h

class Indicators {
public:
  Indicators() {}

  void update(DrivingState drivingState) {
    IndicatorState lastState = state;

    if (state != WARNING) {
      if (drivingState != NEUTRAL || state != CENTER) {
        lastIdle = millis();
      } else if (millis() - lastIdle > 10000) {
        state = WARNING;
      }
    }

    if (state == WARNING) {
      if (drivingState != NEUTRAL) {
        state = CENTER;
      }
    } else {
      if (state == CENTER && drivingState == NEUTRAL) {
        if (steering > STEERING_MAX - 100) {
          state = LEFT;
        } else if (steering < STEERING_MIN + 100) {
          state = RIGHT;
        }
      } else if (state != CENTER) {
        if (steering > STEERING_NEUTRAL - 100 && steering < STEERING_NEUTRAL + 100) {
          state = CENTER;
        }
      }
    }

    if (lastState != state) {
      setState();
    }

    animation.update();
  }

private:
  Animation animation;
  IndicatorState state = CENTER;
  unsigned long lastIdle = 0;

  void setState() {
    Serial.print("INDICATOR ");

    switch (state) {
      case LEFT:
        Serial.println("LEFT");
        left();
        break;
      case CENTER:
        Serial.println("CENTER");
        center();
        break;
      case RIGHT:
        Serial.println("RIGHT");
        right();
        break;
      case WARNING:
        Serial.println("WARNING");
        warning();
        break;
    }
  }

  void left() {
    animation.play(ANIMATE_INDICATORS_LEFT);
  }
  void right() {
    animation.play(ANIMATE_INDICATORS_RIGHT);
  }
  void center() {
    animation.stop();
  }
  void warning() {
    animation.play(ANIMATE_INDICATORS_WARNING);
  }
};

#endif