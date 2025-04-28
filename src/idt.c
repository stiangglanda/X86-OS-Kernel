#include "idt.h"

extern void isr0(void);
extern void isr33(void);  // Add this line for keyboard interrupt

__attribute__((aligned(0x10)))
struct idt_entry idt[256];
struct idtr idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].type_attr = flags;
}

void idt_init(void) {
    // Set up the IDT pointer
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // Clear out the entire IDT, initializing it to zeros
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // Install the ISRs
    idt_set_gate(0, (uint32_t)isr0, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);

    // Install the keyboard ISR (IRQ1 maps to interrupt 33)
    idt_set_gate(33, (uint32_t)isr33, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);

    // Load the IDT pointer
    __asm__ volatile ("lidt %0" : : "m" (idtp));
    __asm__ volatile ("sti"); // set the interrupt flag
}