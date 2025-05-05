#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "isr.h"

// Keyboard I/O ports
#define KEYBOARD_DATA_PORT    0x60
#define KEYBOARD_STATUS_PORT  0x64

// Keyboard IRQ number
#define KEYBOARD_IRQ         1
#define IRQ1                 1  // IRQ number for keyboard

void keyboard_initialize(void);
void keyboard_handler(struct registers* regs);
char keyboard_getchar(void);

#endif