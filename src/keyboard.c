#include "keyboard.h"
#include "pic.h"
#include "terminal.h"

// Basic US keyboard layout
unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
    0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void keyboard_handler(void) {
    unsigned char scancode;

    scancode = inb(0x60);
    
    /* If the top bit of the scan code is set, a key was just released */
    if (scancode & 0x80) {
        // Key release, do nothing for now
    } else {
        /* A key was just pressed */
        if (keyboard_map[scancode]) {
            terminal_putchar(keyboard_map[scancode]);
        }
    }

    pic_send_eoi(1);    // Send End of Interrupt to PIC
}

void keyboard_init(void) {
    // Enable IRQ1 (keyboard)
    outb(PIC1_DATA, inb(PIC1_DATA) & ~(1 << 1));
}