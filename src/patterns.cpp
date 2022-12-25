#include <Arduino.h>

#include "patterns.h"
#include "pins.h"
#include "state.h"

void frame(uint32_t del, int strength1, int strength2) {
  ESP.wdtFeed();
  analogWrite(LED_PIN_1, strength1);
  analogWrite(LED_PIN_2, 0);
  if (changed) {
    return;
  }
  delayMicroseconds(del/2);
  analogWrite(LED_PIN_1, 0);
  analogWrite(LED_PIN_2, strength2);
  if (changed) {
    return;
  }
  delayMicroseconds((del+1)/2);
}

void frame_single(uint32_t del, int channel, int strength) {
  analogWrite(channel, strength);
  if (changed) {
    return;
  }
  delayMicroseconds(del/2);
  analogWrite(channel, 0);
  if (changed) {
    return;
  }
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
    if (changed) {
      return;
    }
    frame(del, strength1, strength2);
  }
}

void blink(uint32_t cycle, int strength) {
  solid_stay(cycle/2, strength, strength);
  solid_stay((cycle+1)/2, 0, 0);
}

void wave(uint32_t cycle, int strength) {
  for (int i = 0; i <= strength; i++) {
    if (changed) {
      return;
    }
    solid_stay(cycle/2/strength, i, i);
  }
  for (int i = strength; i >= 0; i--) {
    if (changed) {
      return;
    }
    solid_stay(cycle/2/strength, i, i);
  }
}

void wave2(uint32_t cycle, int strength1, int strength2) {
  for (int i = 0; i <= strength1; i++) {
    if (changed) {
      return;
    }
    solid_stay(cycle/2/strength1, i, strength2-(int)((float)i/(float)strength1*(float)strength2));
  }
  for (int i = strength1; i >= 0; i--) {
    if (changed) {
      return;
    }
    solid_stay(cycle/2/strength1, (int)((float)i/(float)strength1*(float)strength2), strength1-i);
  }
}

void ILY() {
  solid_stay(1000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(1000);
  solid_stay(1000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(3000);

  solid_stay(1000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(1000);
  solid_stay(3000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(1000);
  solid_stay(1000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(1000);
  solid_stay(1000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(3000);

  solid_stay(3000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(1000);
  solid_stay(1000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(1000);
  solid_stay(3000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(1000);
  solid_stay(3000000, 255, 255);
  reset();
  if (changed) {
    return;
  }
  delay(7000);
}

void reset() {
  analogWrite(LED_PIN_1, 0);
  analogWrite(LED_PIN_2, 0);
}

void off() {
  uint32_t del = 2000;
  reset();
  delayMicroseconds(del);
}