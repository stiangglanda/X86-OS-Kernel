#include "isr.h"
#include "terminal.h"

static const char* exception_messages[] = {
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
    "Machine Check"
};


// Helper function for converting numbers to strings
void itoa(int num, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    if (isNegative)
        str[i++] = '-';

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

void isr_handler(struct registers* regs) {
    terminal_writestring("Interrupt received: ");
    char str[32];
    itoa(regs->int_no, str, 10);
    terminal_writestring(str);
    terminal_writestring("\n");

    if (regs->int_no < 32) {
        terminal_writestring("EXCEPTION: ");
        terminal_writestring(exception_messages[regs->int_no]);
        terminal_writestring("\nError Code: 0x");
        itoa(regs->err_code, str, 16);
        terminal_writestring(str);
        terminal_writestring("\nEIP: 0x");
        itoa(regs->eip, str, 16);
        terminal_writestring(str);
        terminal_writestring("\nCS: 0x");
        itoa(regs->cs, str, 16);
        terminal_writestring(str);
        terminal_writestring("\nEFLAGS: 0x");
        itoa(regs->eflags, str, 16);
        terminal_writestring(str);
        terminal_writestring("\nDS: 0x");
        itoa(regs->ds, str, 16);
        terminal_writestring(str);
        terminal_writestring("\nStack ESP: 0x");
        itoa(regs->esp, str, 16);
        terminal_writestring(str);
        terminal_writestring("\nSystem Halted!\n");
        
        // Add infinite loop to prevent continuing after exception
        for(;;) {
            asm volatile("hlt");
        }
    }
    else if (regs->int_no == ISR_SYSCALL) {
        terminal_writestring("Syscall received!\n");
    }
}

// Helper function to read from I/O ports
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                  : "=a"(ret)
                  : "Nd"(port) );
    return ret;
}