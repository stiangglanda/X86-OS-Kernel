#include "pic.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

void pic_mask_all(void) {
    outb(PIC1_DATA, 0xFF);  // Mask all interrupts on PIC1
    outb(PIC2_DATA, 0xFF);  // Mask all interrupts on PIC2
}

void pic_unmask_irq(uint8_t irq) {
    uint16_t port;
    uint8_t value;
    
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
}

void pic_initialize(void) {
    // Mask all interrupts while initializing
    pic_mask_all();

    // ICW1: Start initialization sequence
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    // ICW2: Set interrupt vector offsets
    outb(PIC1_DATA, 0x20);  // PIC1: 0x20-0x27
    outb(PIC2_DATA, 0x28);  // PIC2: 0x28-0x2F

    // ICW3: Tell PICs how they are connected
    outb(PIC1_DATA, 0x04);  // PIC1: IRQ2 connected to PIC2
    outb(PIC2_DATA, 0x02);  // PIC2: Connected to IRQ2

    // ICW4: Set 8086 mode
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    // Start with all interrupts masked
    pic_mask_all();
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_COMMAND, 0x20);
    outb(PIC1_COMMAND, 0x20);
}