# pico-button.c

## Installation

Install with [clib(1)](https://github.com/clibs/clib):

```sh
$ clib install jkroso/pico-button.c
```

## Api

`create_button(pin, onchange)`: It will set the pin to pull up. It returns a `button_t` struct

```c
typedef struct button_t {
  uint8_t pin;
  bool state;
  void (*onchange)(struct button_t *button);
} button_t;
```

## Example

```c
#include "pico-button/button.c"

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
```
