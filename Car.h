#include "Controller.h"
#include "Indicators.h"
#include "Headlights.h"
#include "Enums.h"

#ifndef Car_h
#define Car_h

class Car {
public:
  Car() {}

  void toggleLights() {
    headlights.next();
  }

  void update() {
    DrivingState lastState = state;

    if (throttlePulses < THROTTLE_MAX + 100) {
      throttle = throttlePulses;
    }
    if (steeringPulses < STEERING_MAX + 100) {
      steering = steeringPulses;
    }

    if (throttle > THROTTLE_NEUTRAL + 100) {
      state = DRIVING;
      didBrake = false;
    } else if (throttle < THROTTLE_NEUTRAL - 100) {
      if (didBrake) {
        state = REVERSING;
      } else {
        state = BRAKING;
      }
    } else {
      if (state == BRAKING) {
        didBrake = true;
      }
      state = NEUTRAL;
    }

    if (lastState != state) {
      setState();
    }

    indicators.update(state);
  }

private:
  Indicators indicators;
  Headlights headlights;
  DrivingState state = NEUTRAL;
  bool didBrake = false;

  void setState() {
    Serial.print("THROTTLE ");

    switch (state) {
      case DRIVING:
        Serial.println("DRIVE");
        brakes(false);
        reverse(false);
        break;
      case NEUTRAL:
        Serial.println("NEUTRAL");
        brakes(false);
        break;
      case BRAKING:
        Serial.println("BRAKE");
        brakes(true);
        break;
      case REVERSING:
        Serial.println("REVERSE");
        reverse(true);
        break;
    }
  }

  void brakes(bool on) {
    //Rear Left:  12-15   Rear Right  8-11
    setColorLoop(8, 8, on ? CRGB::Red : CRGB::Black);
    FastLED.show();
  }
  void reverse(bool on) {
    //Rear Left:  12-15   Rear Right  8-11
    setColorLoop(8, 8, on ? CRGB::White : CRGB::Black);
    FastLED.show();
  }
};

#endif