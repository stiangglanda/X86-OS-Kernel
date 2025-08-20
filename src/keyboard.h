#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "isr.h"

// Keyboard ports
#define KEYBOARD_DATA_PORT    0x60
#define KEYBOARD_STATUS_PORT  0x64
#define KEYBOARD_COMMAND_PORT 0x64

// Keyboard IRQ definitions
#define KEYBOARD_IRQ         1
#define IRQ1                 1

void keyboard_initialize(void);
void keyboard_handler(void);
char keyboard_getchar(void);

#endif