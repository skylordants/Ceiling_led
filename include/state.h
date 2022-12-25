#ifndef __STATE_H__
#define __STATE_H__

extern bool changed;
extern int state;
extern unsigned long last_press;

void IRAM_ATTR changeState();

#endif