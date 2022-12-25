#ifndef __PINS_H__
#define __PINS_H__

#define BOARD_ESP32 1
#define BOARD_ESP01 2

#define BOARD BOARD_ESP01

#if BOARD == BOARD_ESP32
#define LED_PIN_1 22
#define LED_PIN_2 23
#define BUTTON_PIN 0
#elif BOARD == BOARD_ESP01
#define LED_PIN_1 0
#define LED_PIN_2 2
#define BUTTON_PIN 1
#endif

#endif