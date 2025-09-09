#include "keyboard.h"
#include "idt.h"
#include "pic.h"
#include "terminal.h"

extern void irq1_handler(void);

#define KEYBOARD_BUFFER_SIZE 256
static char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static int buffer_start = 0;
static int buffer_end = 0;

static char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0,
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void keyboard_handler(void) {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    
    if (!(scancode & 0x80) && scancode < sizeof(scancode_to_ascii)) {
        char ascii = scancode_to_ascii[scancode];
        if (ascii != 0) {
            terminal_putchar(ascii);
        }
    }

    pic_send_eoi(KEYBOARD_IRQ);
}

void keyboard_initialize(void) {
    terminal_writestring("Keyboard: Starting initialization...\n");
    idt_set_gate(33, (uint32_t)irq1_handler, 0x08, 0x8E);
    
    pic_unmask_irq(1);
}


char keyboard_getchar(void) {
    if (buffer_start == buffer_end) {
        return 0;
    }
    
    char c = keyboard_buffer[buffer_start];
    buffer_start = (buffer_start + 1) % KEYBOARD_BUFFER_SIZE;
    return c;
}