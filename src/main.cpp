#include <Arduino.h>
#include "ESP8266WiFi.h"

#include "patterns.h"
#include "pins.h"
#include "state.h"

#define ACTIVETIME 3600000

//PWM stuff
const int pwm_freq = 5000; // 200 us for one cycle so 1 ms changing should be slow enough?
const int pwm_resolution = 8;

void setup() {
  //Setup led channels
  pinMode(LED_PIN_1, OUTPUT_OPEN_DRAIN);
  pinMode(LED_PIN_2, OUTPUT_OPEN_DRAIN);
  analogWriteFreq(pwm_freq);
  reset();

  Serial.begin(74880);
  //Setup state management
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), changeState, FALLING);


  // modem sleep?
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.forceSleepBegin();
  delay(1);
}

void loop() {
  if (millis()-last_press < ACTIVETIME) {
    changed = false;
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
      case 10:
        ILY();
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