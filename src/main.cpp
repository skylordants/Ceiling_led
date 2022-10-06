#include <Arduino.h>

#define LED_PIN_1 22
#define LED_PIN_2 23

#define DEBOUNCETIME 100
#define ACTIVETIME 3600000

bool active = true;
unsigned long last_active = 0;

//PWM stuff
const int pwm_freq = 5000; // 200 us for one cycle so 1 ms changing should be slow enough?
const int led_channel_1 = 0;
const int led_channel_2 = 1;
const int pwm_resolution = 8;

//Different led patterns
void twinkle(uint32_t del, int strength1, int strength2) {
  ledcWrite(led_channel_1, strength1);
  ledcWrite(led_channel_2, 0);
  delayMicroseconds(del/2);
  ledcWrite(led_channel_1, 0);
  ledcWrite(led_channel_2, strength2);
  delayMicroseconds((del+1)/2);
}

void twinkle_single(uint32_t del, int channel, int strength) {
  ledcWrite(channel, strength);
  delayMicroseconds(del/2);
  ledcWrite(channel, 0);
  delayMicroseconds((del+1)/2);
}

void solid(int strength) {
  uint32_t del = 1000;
  twinkle(del, strength, strength);
}

void solid_stay(uint32_t time, int strength1, int strength2) {
  uint32_t del = 1000;
  unsigned long s = micros();
  while(micros()-s < time) {
    twinkle(del, strength1, strength2);
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

void blink(uint32_t del, int strength) {
  solid_stay(del, strength, strength);
  solid_stay(del, 0, 0);
}

void wave(uint32_t cycle, int strength) {
  for (int i = 0; i <= strength; i++) {
    solid_stay(cycle/2/strength, i, i);
  }
  for (int i = strength; i >= 0; i--) {
    solid_stay(cycle/2/strength, i, i);
  }
}

void wave2(uint32_t cycle, int strength) {
  for (int i = 0; i <= strength; i++) {
    solid_stay(cycle/2/strength, i, strength-i);
  }
  for (int i = strength; i >= 0; i--) {
    solid_stay(cycle/2/strength, i, strength-i);
  }
}

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
  attachInterrupt(0, changeState, RISING);
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
        solid(255);
        break;
      case 2:
        solid(100);
        break;
      case 3:
        solid(50);
        break;
      case 4:
        solid(5);
        break;
      case 5:
        blink(1000000, 255);
        break;
      case 6:
        twinkle(2000000, 255, 255);
        break;
      case 7:
        twinkle(2000000, 50, 50);
        break;
      case 8:
        wave(2000000, 200);
        break;
      case 9:
        wave2(2000000, 200);
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