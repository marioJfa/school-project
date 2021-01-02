#include "motorslibrary.h"
Motor left_motor(9);
int led = 9;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  left_motor.led_on(led);
  delay(1000);
  left_motor.led_off(led);
  delay(1000);
}
