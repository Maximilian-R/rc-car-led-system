//#include <FastLED.h>
#include <Animation.h>

#define REFRESH_INTERVAL 10  //ms

// LEDS -------------------------
#define NUM_LEDS 144
#define LED_PIN 6
#define VOLTS 5
#define MAX_AMPS 500
// ------------------------------

// Button ----------------------
#define DEBOUNCE_DELAY 50  //ms
#define BUTTON_PIN 4
// -----------------------------

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

//CRGB leds[NUM_LEDS];
Animation animation1;

unsigned long lastRender = 0;

int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

volatile long throttleStartTime = 0;
volatile long throttleCurrentTime = 0;
volatile long throttlePulses = 0;
int throttle;
volatile long steeringStartTime = 0;
volatile long steeringCurrentTime = 0;
volatile long steeringPulses = 0;
int steering;

enum HeadlightState {
  OFF,
  LEDS,
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

class Headlights {
public:
  void next() {
    Serial.print("LIGHTS ");

    switch (state) {
      case OFF:
        Serial.println("OFF");
        state = LEDS;
        off();
        break;
      case LEDS:
        Serial.println("LEDS");
        state = HALF;
        leds();
        break;
      case HALF:
        Serial.println("HALF");
        state = FULL;
        halfLight();
        break;
      case FULL:
        Serial.println("FULL");
        state = OFF;
        fullLight();
        break;
    }
  }

private:
  HeadlightState state = OFF;
  void off() {}
  void leds() {}
  void halfLight() {}
  void fullLight() {}
};

class Indicators {
public:
  Indicators() {}

  update(DrivingState drivingState) {
    IndicatorState lastState = state;

    if (state != WARNING) {
      if (drivingState != NEUTRAL) {
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
  }

private:
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
    animation1.setAnimation(1000, true, animate_indicator_left, 4);
  }
  void right() {
    animation1.setAnimation(1000, true, animate_indicator_right, 4);
  }
  void center() {
    animation1.alive = false;
  }
  void warning() {
    animation1.setAnimation(1000, true, animate_indicator_warning, 2);
  }
};

class Car {
public:
  Car() {}

  update() {
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

  void brakes(bool on) {}
  void reverse(bool on) {}
};

Car car;
Headlights headlights;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  //FastLED.addLeds<WS2812, LED_PIN>(leds, NUM_LEDS);
  // set max volt/amp for FASTLED

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(THROTTLE_PIN, INPUT_PULLUP);
  pinMode(STEERING_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(THROTTLE_PIN), throttleChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(STEERING_PIN), steeringChange, CHANGE);
}

void loop() {
  readButton();

  if (millis() - lastRender >= REFRESH_INTERVAL) {
    lastRender = millis();

    car.update();

    animation1.update();
  }
}

void readButton() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        Serial.println("Button Released");
      } else {
        Serial.println("Button Pushed");
        headlights.next();
      }
    }
  }
  lastButtonState = reading;
}

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

// FIND PWM of receiver channels
void debugInputs() {
  Serial.print("Throttle:");
  Serial.print(throttle);
  Serial.print(",");
  Serial.print("Steering:");
  Serial.println(steering);
}