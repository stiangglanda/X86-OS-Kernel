#include "pic.h"

/* Helper functions to communicate with the PIC */
static inline void io_wait(void)
{
    asm volatile("outb %%al, $0x80" : : "a"(0));
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void pic_init(void)
{
    uint8_t a1, a2;
 
    // Save masks
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);
 
    // Start the initialization sequence
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Set vector offset
    outb(PIC1_DATA, 0x20); // Start vectors at 32
    io_wait();
    outb(PIC2_DATA, 0x28); // Start vectors at 40
    io_wait();

    // Tell Master PIC that there is a slave PIC at IRQ2
    outb(PIC1_DATA, 4);
    io_wait();
    // Tell Slave PIC its cascade identity
    outb(PIC2_DATA, 2);
    io_wait();
 
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();
 
    // Restore saved masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

void pic_send_eoi(unsigned char irq)
{
    if(irq >= 8)
        outb(PIC2_COMMAND, 0x20);
    outb(PIC1_COMMAND, 0x20);
}