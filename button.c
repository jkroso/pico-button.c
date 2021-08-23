#ifndef PICO_BUTTON_C
#define PICO_BUTTON_C

#include "pico/stdlib.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "pico-gpio-interrupt/gpio-interrupt.c"

typedef struct button_t {
  uint8_t pin;
  bool state;
  void (*onchange)(struct button_t *button);
} button_t;

long long int handle_button_alarm(long int a, void *p) {
  button_t *b = (button_t *)(p);
  bool state = gpio_get(b->pin);
  if (state != b->state) {
    b->state = state;
    b->onchange(b);
  }
  return 0;
}

void handle_button_interrupt(void *p) {
  button_t *b = (button_t *)(p);
  bool state = gpio_get(b->pin);
  add_alarm_in_us(200, handle_button_alarm, b, true);
}

button_t * create_button(int pin, void (*onchange)(button_t *)) {
  button_t *b = (button_t *)(malloc(sizeof(button_t)));
  listen(pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, handle_button_interrupt, b);
  b->pin = pin;
  b->onchange = onchange;
  b->state = gpio_get(pin);
  return b;
}

#endif
