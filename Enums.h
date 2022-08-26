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

#endif