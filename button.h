#ifndef PICO_BUTTON_H
#define PICO_BUTTON_H

typedef struct button_t {
  uint8_t pin;
  bool state;
  void (*onchange)(struct button_t *button);
} button_t;

long long int handle_button_alarm(long int a, void *p);
void handle_button_interrupt(void *p);
button_t * create_button(int pin, void (*onchange)(button_t *));

#endif
