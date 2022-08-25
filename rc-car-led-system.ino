#include "Controller.h"
#include "Car.h"
#include "Button.h"
#include "Leds.h"

#define REFRESH_INTERVAL 10  //ms

Car car;
Button button;

unsigned long lastRender = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  setupLEDS(); 

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(THROTTLE_PIN, INPUT_PULLUP);
  pinMode(STEERING_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(THROTTLE_PIN), throttleChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(STEERING_PIN), steeringChange, CHANGE);

  button.setCallback(onButtonPress);
}

void loop() {
  button.update();

  if (millis() - lastRender >= REFRESH_INTERVAL) {
    lastRender = millis();

    car.update();
  }
}

void onButtonPress() {
  car.toggleLights();
}

// FIND PWM of receiver channels
void debugInputs() {
  Serial.print("Throttle:");
  Serial.print(throttle);
  Serial.print(",");
  Serial.print("Steering:");
  Serial.println(steering);
}