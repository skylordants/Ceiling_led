#ifndef __patterns_h__
#define __patterns_h__

void frame(uint32_t del, int strength1, int strength2);

void solid(int strength1, int strength2);

void solid_stay(uint32_t time, int strength1, int strength2);

void blink(uint32_t cycle, int strength);

void wave(uint32_t cycle, int strength);

void wave2(uint32_t cycle, int strength1, int strength2);

void ILY();


void reset();

void off();

#endif