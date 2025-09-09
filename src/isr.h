#ifndef ISR_H
#define ISR_H

#include <stdint.h>

#define ISR_DIVIDE_BY_ZERO    0
#define ISR_DEBUG             1
#define ISR_NMI              2
#define ISR_BREAKPOINT       3
#define ISR_OVERFLOW         4
#define ISR_BOUND_RANGE      5
#define ISR_INVALID_OPCODE   6
#define ISR_DEVICE_NOT_AVAILABLE 7
#define ISR_DOUBLE_FAULT     8
#define ISR_INVALID_TSS      10
#define ISR_SEGMENT_NOT_PRESENT 11
#define ISR_STACK_SEGMENT_FAULT 12
#define ISR_GENERAL_PROTECTION 13
#define ISR_PAGE_FAULT       14
#define ISR_TIMER            32
#define ISR_KEYBOARD         33
#define ISR_SYSCALL         128

struct registers {
    // Pushed by pusha
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // Pushed by our ASM stub
    uint32_t ds;
    // Pushed by CPU/ASM stub
    uint32_t int_no, err_code;
    // Automatically pushed by the processor
    uint32_t eip, cs, eflags;
} __attribute__((packed));

void isr_handler(struct registers* regs);
void itoa(int num, char* str, int base);

#endif