#include "isr.h"
#include "terminal.h"

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

// Helper function to convert int to string
void int_to_string(int num, char* str) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    int i = 0;
    int is_negative = 0;
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num = num / 10;
    }
    
    if (is_negative) {
        str[i++] = '-';
    }
    
    str[i] = '\0';
    
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void isr_handler(registers_t* regs) {
    if (regs->int_no == 13) {
        terminal_writestring("General Protection Fault (INT 13)\n");
        terminal_writestring("Error Code: ");
        // Convert error code to string and print it
        char err_str[16];
        int_to_string(regs->err_code, err_str);
        terminal_writestring(err_str);
        terminal_writestring("\n");
        
        // Print relevant register values
        terminal_writestring("CS: ");
        int_to_string(regs->cs, err_str);
        terminal_writestring(err_str);
        terminal_writestring(" EIP: ");
        int_to_string(regs->eip, err_str);
        terminal_writestring(err_str);
        terminal_writestring("\n");
    } else {
        terminal_writestring("Interrupt received: ");
        // Simple number to string conversion for the interrupt number
        char int_str[3] = {'0' + (regs->int_no / 10), '0' + (regs->int_no % 10), '\0'};
        terminal_writestring(int_str);
        terminal_writestring("\n");
    }
}