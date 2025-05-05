#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// IDT entry structure
struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

// IDT pointer structure
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Function declarations
void idt_initialize(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

// ISR declarations
extern void isr0(void);    // Divide by zero
extern void isr1(void);    // Debug
extern void isr2(void);    // Non-maskable interrupt
extern void isr3(void);    // Breakpoint
extern void isr4(void);    // Overflow
extern void isr5(void);    // Bound range exceeded
extern void isr6(void);    // Invalid opcode
extern void isr7(void);    // Device not available
extern void isr8(void);    // Double fault
extern void isr9(void);    // Coprocessor segment overrun
extern void isr10(void);   // Invalid TSS
extern void isr11(void);   // Segment not present
extern void isr12(void);   // Stack segment fault
extern void isr13(void);   // General protection fault
extern void isr14(void);   // Page fault
extern void isr128(void);  // System call

#endif