#include "Animation.h"

// PWM INPUTS ------------------
#define THROTTLE_PIN 3
#define STEERING_PIN 2

#define THROTTLE_MIN 956
#define THROTTLE_MAX 2104
#define THROTTLE_NEUTRAL 1508
#define STEERING_MIN 1130
#define STEERING_MAX 1860
#define STEERING_NEUTRAL 1520
// -----------------------------

extern volatile long throttleStartTime;
extern volatile long throttleCurrentTime;
extern volatile long throttlePulses;
extern int throttle;
extern volatile long steeringStartTime;
extern volatile long steeringCurrentTime;
extern volatile long steeringPulses;
extern int steering;

void throttleChange();
void steeringChange();