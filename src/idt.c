#include "idt.h"

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr13(void);
extern void isr14(void);
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
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // Clear out the entire IDT
    __builtin_memset(&idt, 0, sizeof(struct idt_entry) * 256);

    // Install the CPU exception ISRs
    idt_set_gate(0, (uint32_t)isr0, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Divide by Zero
    idt_set_gate(1, (uint32_t)isr1, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Debug
    idt_set_gate(2, (uint32_t)isr2, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // NMI
    idt_set_gate(3, (uint32_t)isr3, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Breakpoint
    idt_set_gate(4, (uint32_t)isr4, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Overflow
    idt_set_gate(5, (uint32_t)isr5, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Bound Range
    idt_set_gate(6, (uint32_t)isr6, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Invalid Opcode
    idt_set_gate(7, (uint32_t)isr7, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Device Not Available
    idt_set_gate(8, (uint32_t)isr8, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT);  // Double Fault
    idt_set_gate(13, (uint32_t)isr13, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT); // General Protection Fault
    idt_set_gate(14, (uint32_t)isr14, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT); // Page Fault

    // Load the IDT pointer
    __asm__ volatile ("lidt %0" : : "m" (idtp));
}