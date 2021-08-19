#include "./deps/GPIO-Interrupt/GPIO-Interrupt.c"
#include "./src/Button.c"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

void onchange(button_t *button_p) {
  button_t *button = (button_t*)button_p;
  printf("Button on pin %d changed state to %d\n", button->pin, button->state);
}

int main() {
  stdio_init_all();
  button_t *b = create_button(21, onchange);
  printf("Button created and it's state is %d\n", b->state);
  while (true) tight_loop_contents();
  return 0;
}
