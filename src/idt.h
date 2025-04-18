#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// Segment selectors
#define KERNEL_CS 0x08

// IDT gate types
#define IDT_GATE_TYPE_INTERRUPT 0x8E
#define IDT_GATE_TYPE_TRAP     0x8F

// Structure for IDT entry
struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t base_high;
} __attribute__((packed));

// Structure for IDTR
struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Function declarations
void idt_init(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

#endif