#include "gdt.h"

// GDT entry structure using 64-bit descriptor format
struct gdt_entry {
    uint64_t descriptor;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gp;

struct gdt_entry gdt[3];

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;

    // Create the high 32 bit segment
    descriptor  = limit       & 0x000F0000;     // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;     // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;     // set base bits 23:16
    descriptor |= base        & 0xFF000000;     // set base bits 31:24

    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;

    // Create the low 32 bit segment
    descriptor |= base  << 16;                   // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;           // set limit bits 15:0

    return descriptor;
}

extern void gdt_flush(uint32_t);

void gdt_install(void)
{
    // Setup GDT pointer and limit
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (uint32_t)&gdt;

    // Null descriptor
    gdt[0].descriptor = create_descriptor(0, 0, 0);

    // Code segment descriptor
    gdt[1].descriptor = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));

    // Data segment descriptor
    gdt[2].descriptor = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));

    // Load GDT
    gdt_flush((uint32_t)&gp);
}