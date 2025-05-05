#include "gdt.h"

struct gdt_entry gdt[3];
struct gdt_ptr gp;

// Setup a GDT entry
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[num].access = access;
}

// Initialize GDT
void gdt_initialize(void) {
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (uint32_t)&gdt;

    // Null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);

    // Code segment: base=0, limit=4GB, gran=4KB blocks, 32-bit, ring0
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment: base=0, limit=4GB, gran=4KB blocks, 32-bit, ring0
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Load GDT and update segment registers
    asm volatile(
        "lgdt %0\n"
        "movw $0x10, %%ax\n"
        "movw %%ax, %%ds\n"
        "movw %%ax, %%es\n"
        "movw %%ax, %%fs\n"
        "movw %%ax, %%gs\n"
        "movw %%ax, %%ss\n"
        "ljmp $0x08, $1f\n"
        "1:\n"
        : : "m"(gp) : "ax");
}