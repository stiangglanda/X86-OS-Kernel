#include "gdt.h"
#include "idt.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "pic.h"
#include "terminal.h"
#include "keyboard.h"
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

void test_gdt(void) {
    terminal_writestring("Test 1: Checking GDT segments...\n");
    
    // Try to write to code segment
    terminal_writestring("Writing to code segment...\n");
    
    // Direct attempt to write to code segment using CS selector
    asm volatile(
        "mov $0x08, %%ax\n"    // Load code segment selector (0x08)
        "mov %%ax, %%ds\n"     // Try to use code segment as data segment
        "movl $0, (0x1000)"    // Try to write to memory through segment
        :
        :
        : "ax", "memory"
    );
    
    // If we get here, protection failed
    terminal_writestring("Code segment write succeeded - GDT protection failed!\n");
}

void test_interrupt(void) {
    terminal_writestring("Testing division by zero...\n");
    int a = 10;
    int b = 0;
    __asm__ volatile("div %0" : : "r" (b));  // Force division by zero
}

void kernel_main(void) 
{
    /* Initialize GDT */
    gdt_install();

    /* Initialize IDT */
    idt_init();

    /* Initialize PIC */
    pic_init();
    
    /* Initialize terminal interface */
    terminal_initialize();
    
    /* Initialize keyboard */
    keyboard_init();
    
    /* Enable interrupts */
    __asm__ volatile ("sti");
    
    terminal_writestring("System initialized!\n");
    terminal_writestring("Start typing...\n");

    // Main loop
    //for(;;);
}