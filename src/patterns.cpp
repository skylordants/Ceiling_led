#include <Arduino.h>
#include "patterns.h"

void frame(uint32_t del, int strength1, int strength2) {
  ledcWrite(led_channel_1, strength1);
  ledcWrite(led_channel_2, 0);
  delayMicroseconds(del/2);
  ledcWrite(led_channel_1, 0);
  ledcWrite(led_channel_2, strength2);
  delayMicroseconds((del+1)/2);
}

void frame_single(uint32_t del, int channel, int strength) {
  ledcWrite(channel, strength);
  delayMicroseconds(del/2);
  ledcWrite(channel, 0);
  delayMicroseconds((del+1)/2);
}

void solid(int strength1, int strength2) {
  uint32_t del = 1000;
  frame(del, strength1, strength2);
}

void solid_stay(uint32_t time, int strength1, int strength2) {
  uint32_t del = 1000;
  unsigned long s = micros();
  while(micros()-s < time) {
    frame(del, strength1, strength2);
  }
}

void blink(uint32_t cycle, int strength) {
  solid_stay(cycle/2, strength, strength);
  solid_stay((cycle+1)/2, 0, 0);
}

void wave(uint32_t cycle, int strength) {
  for (int i = 0; i <= strength; i++) {
    solid_stay(cycle/2/strength, i, i);
  }
  for (int i = strength; i >= 0; i--) {
    solid_stay(cycle/2/strength, i, i);
  }
}

void wave2(uint32_t cycle, int strength1, int strength2) {
  for (int i = 0; i <= strength1; i++) {
    solid_stay(cycle/2/strength1, i, strength2-(int)((float)i/(float)strength1*(float)strength2));
  }
  for (int i = strength1; i >= 0; i--) {
    solid_stay(cycle/2/strength1, (int)((float)i/(float)strength1*(float)strength2), strength1-i);
  }
}

void reset() {
  ledcWrite(led_channel_1, 0);
  ledcWrite(led_channel_2, 0);
}

void off() {
  uint32_t del = 2000;
  reset();
  delayMicroseconds(del);
}