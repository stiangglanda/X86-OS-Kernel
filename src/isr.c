#include "isr.h"
#include "terminal.h"
#include "keyboard.h"

// Array of messages for the first 32 CPU exceptions
static const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(struct registers *r) {
    if (r->int_no < 32) {
        terminal_writestring("Received interrupt: ");
        terminal_writestring(exception_messages[r->int_no]);
        terminal_writestring("\n");
        for(;;);
    } else if (r->int_no == 33) {
        keyboard_handler();
    }
}