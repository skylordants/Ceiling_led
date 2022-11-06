#include <Arduino.h>
#include "patterns.h"
#include "pins.h"

#define DEBOUNCETIME 100
#define ACTIVETIME 3600000

bool active = true;
unsigned long last_active = 0;

//PWM stuff
const int pwm_freq = 5000; // 200 us for one cycle so 1 ms changing should be slow enough?
const int pwm_resolution = 8;

//State management
int state = 0;

unsigned long last_press = 0;

void IRAM_ATTR changeState() {
  if (millis()-last_press > DEBOUNCETIME) {
    state++;
    last_press = millis();
    active = true;
  }
}


void setup() {
  //Setup led channels
  ledcSetup(led_channel_1, pwm_freq, pwm_resolution);
  ledcSetup(led_channel_2, pwm_freq, pwm_resolution);
  ledcAttachPin(LED_PIN_1, led_channel_1);
  ledcAttachPin(LED_PIN_2, led_channel_2);
  reset();

  //Setup state management
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), changeState, RISING);
  last_active = millis();

  Serial.begin(115200);
}

void loop() {
  if (millis()-last_press < ACTIVETIME) {
    switch (state) {
      case 0:
        off();
        break;
      case 1:
        solid(255, 255);
        break;
      case 2:
        solid(100, 100);
        break;
      case 3:
        solid(50, 50);
        break;
      case 4:
        solid(5, 5);
        break;
      case 5:
        blink(2000000, 255);
        break;
      case 6:
        frame(2000000, 255, 255);
        break;
      case 7:
        frame(2000000, 50, 50);
        break;
      case 8:
        wave(2000000, 200);
        break;
      case 9:
        wave2(2000000, 200, 200);
        break;
      default:
        state = 0;
        break;
    }
  }
  else {
    reset();
    state = 0;
    delay(1000);
  }
}