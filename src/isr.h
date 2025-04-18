#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// Define a struct for registers
struct registers {
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, esp; // Pushed by pusha
    uint32_t ebx, edx, ecx, eax; // Pushed by pusha
    uint32_t int_no, err_code;   // Interrupt number and error code
    uint32_t eip, cs, eflags;    // Pushed by the processor automatically
} __attribute__((packed));

void isr_handler(struct registers *r);

#endif