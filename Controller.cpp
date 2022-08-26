#include "Controller.h"

volatile long throttleStartTime = 0;
volatile long throttleCurrentTime = 0;
volatile long throttlePulses = 0;
int throttle;
volatile long steeringStartTime = 0;
volatile long steeringCurrentTime = 0;
volatile long steeringPulses = 0;
int steering;

void throttleChange() {
  throttleCurrentTime = micros();
  if (throttleCurrentTime > throttleStartTime) {
    throttlePulses = throttleCurrentTime - throttleStartTime;
    throttleStartTime = throttleCurrentTime;
  }
}

void steeringChange() {
  steeringCurrentTime = micros();
  if (steeringCurrentTime > steeringStartTime) {
    steeringPulses = steeringCurrentTime - steeringStartTime;
    steeringStartTime = steeringCurrentTime;
  }
}

// https://www.youtube.com/watch?v=UZKxUFkwCc8&ab_channel=TheBoredRobot
// find PWM of receiver channels
void debugInputs() {
  Serial.print("Throttle:");
  Serial.print(throttle);
  Serial.print(",");
  Serial.print("Steering:");
  Serial.println(steering);
}