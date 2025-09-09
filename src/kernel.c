#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "keyboard.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

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
    
    asm volatile("sti");
    
    terminal_writestring("System running...\n");
    terminal_writestring("Type something: ");

    while(1) {
        asm volatile("hlt");
    }
}