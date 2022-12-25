#include <Arduino.h>

#include "state.h"

#define DEBOUNCETIME 300

bool changed = false;

//State management
int state = 0;

unsigned long last_press = 0;

void IRAM_ATTR changeState() {
  if (millis()-last_press > DEBOUNCETIME && !changed) {
    printf("%d, %d", state, state+1);
    state++;
    last_press = millis();
	changed = true;
  }
}