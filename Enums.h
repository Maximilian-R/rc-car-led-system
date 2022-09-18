#ifndef Enums_h
#define Enums_h

enum HeadlightState {
  OFF,
  LED_LIGHT,
  HALF,
  FULL
};

enum IndicatorState {
  LEFT,
  CENTER,
  RIGHT,
  WARNING
};

enum DrivingState {
  DRIVING,
  NEUTRAL,
  BRAKING,
  REVERSING
};

enum AnimationType {
  ANIMATE_SIRENS,
  ANIMATE_INDICATORS_LEFT,
  ANIMATE_INDICATORS_RIGHT,
  ANIMATE_INDICATORS_WARNING
};

#endif