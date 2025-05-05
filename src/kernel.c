#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "gdt.h"
#include "idt.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
    terminal_initialize();
    terminal_writestring("Starting kernel...\n");
    
    terminal_writestring("Initializing GDT...\n");
    gdt_initialize();
    terminal_writestring("GDT initialized\n");

    terminal_writestring("Initializing IDT...\n");
    idt_initialize();
    terminal_writestring("IDT initialized\n");
    
    // Clear interrupts first
    asm volatile("cli");
    
    // Enable interrupts
    asm volatile("sti");
    
    terminal_writestring("System running...\n");
    
    terminal_writestring("Triggering software interrupt...\n");
    // Test software interrupt
    //asm volatile("int $0x80");
    
    terminal_writestring("After interrupt\n");
    terminal_writestring("Entering infinite loop...\n");

    // More stable infinite loop with a halt instruction
    while(1) {
        asm volatile("hlt");
    }
}