#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "keyboard.h"

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

    terminal_writestring("Initializing PIC...\n");
    pic_initialize();
    terminal_writestring("PIC initialized\n");

    terminal_writestring("Initializing IDT...\n");
    idt_initialize();
    terminal_writestring("IDT initialized\n");

    terminal_writestring("Initializing keyboard...\n");
    keyboard_initialize();
    terminal_writestring("Keyboard initialized\n");
    
    // Enable interrupts
    asm volatile("sti");
    
    terminal_writestring("System running...\n");
    terminal_writestring("Type something: ");

    // Main loop - just halt CPU until next interrupt
    while(1) {
        asm volatile("hlt");
    }
}