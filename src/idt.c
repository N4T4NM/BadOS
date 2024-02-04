#include <kernel/idt.h>
#include <std.h>

IDTGate idt[IDT_ENTRIES];
IDTRegister idt_reg;

void IDTSetGate(int32 n, uint32 handler) {
    idt[n].low_offset = LOWORD(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = HIWORD(handler);
}
void IDTSet() {
    idt_reg.base = (uint32)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(IDTGate) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}