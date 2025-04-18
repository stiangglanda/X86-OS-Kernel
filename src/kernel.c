#include "gdt.h"
#include "idt.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
 
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
    
    // Try to write to NULL segment
    terminal_writestring("Writing to NULL segment (0x00)...\n");
    uint32_t *null_ptr = (uint32_t*)0x00;
    *null_ptr = 0;  // Should fault
    
    terminal_writestring("NULL segment write succeeded - BAD!\n");
    
    // Try to write to code segment
    terminal_writestring("Writing to code segment (0x08)...\n");
    uint32_t *code_ptr = (uint32_t*)0x08;
    *code_ptr = 0;  // Should fault
    
    terminal_writestring("Code segment write succeeded - BAD!\n");
    
    // Try to execute from data segment
    terminal_writestring("Trying to jump to data segment (0x10)...\n");
    void (*data_ptr)(void) = (void*)0x10;
    data_ptr();  // Should fault
    
    terminal_writestring("Data segment execute succeeded - BAD!\n");
}

void test_interrupt(void) {
    int a = 10;
    int b = 0;
    int c = a / b;  // This will trigger a division by zero exception
}

void kernel_main(void) 
{
    /* Initialize GDT */
    gdt_install();

    /* Initialize IDT */
	idt_init();
    
    /* Initialize terminal interface */
    terminal_initialize();
 
    terminal_writestring("GDT installed...\n");
    
    // Simple test - try accessing different segments
    terminal_writestring("Testing GDT...\n");
    //test_gdt();  // This should cause a fault

	test_interrupt();
    
    terminal_writestring("If you see this, GDT protection failed!\n");
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
}