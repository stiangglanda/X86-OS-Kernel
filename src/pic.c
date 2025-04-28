#include "pic.h"

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