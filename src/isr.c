#include <kernel/isr.h>
#include <kernel/idt.h>
#include <drivers/ports.h>
#include <drivers/tty.h>

ISRCallback interrupt_handlers[256];

static bool s_installed;

void ISRInstall() {
    IDTSetGate(0, (uint32)isr0);
    IDTSetGate(1, (uint32)isr1);
    IDTSetGate(2, (uint32)isr2);
    IDTSetGate(3, (uint32)isr3);
    IDTSetGate(4, (uint32)isr4);
    IDTSetGate(5, (uint32)isr5);
    IDTSetGate(6, (uint32)isr6);
    IDTSetGate(7, (uint32)isr7);
    IDTSetGate(8, (uint32)isr8);
    IDTSetGate(9, (uint32)isr9);
    IDTSetGate(10, (uint32)isr10);
    IDTSetGate(11, (uint32)isr11);
    IDTSetGate(12, (uint32)isr12);
    IDTSetGate(13, (uint32)isr13);
    IDTSetGate(14, (uint32)isr14);
    IDTSetGate(15, (uint32)isr15);
    IDTSetGate(16, (uint32)isr16);
    IDTSetGate(17, (uint32)isr17);
    IDTSetGate(18, (uint32)isr18);
    IDTSetGate(19, (uint32)isr19);
    IDTSetGate(20, (uint32)isr20);
    IDTSetGate(21, (uint32)isr21);
    IDTSetGate(22, (uint32)isr22);
    IDTSetGate(23, (uint32)isr23);
    IDTSetGate(24, (uint32)isr24);
    IDTSetGate(25, (uint32)isr25);
    IDTSetGate(26, (uint32)isr26);
    IDTSetGate(27, (uint32)isr27);
    IDTSetGate(28, (uint32)isr28);
    IDTSetGate(29, (uint32)isr29);
    IDTSetGate(30, (uint32)isr30);
    IDTSetGate(31, (uint32)isr31);

    // Remap the PIC
    PortWriteUInt8(0x20, 0x11);
    PortWriteUInt8(0xA0, 0x11);
    PortWriteUInt8(0x21, 0x20);
    PortWriteUInt8(0xA1, 0x28);
    PortWriteUInt8(0x21, 0x04);
    PortWriteUInt8(0xA1, 0x02);
    PortWriteUInt8(0x21, 0x01);
    PortWriteUInt8(0xA1, 0x01);
    PortWriteUInt8(0x21, 0x0);
    PortWriteUInt8(0xA1, 0x0); 

    // Install the IRQs
    IDTSetGate(32, (uint32)irq0);
    IDTSetGate(33, (uint32)irq1);
    IDTSetGate(34, (uint32)irq2);
    IDTSetGate(35, (uint32)irq3);
    IDTSetGate(36, (uint32)irq4);
    IDTSetGate(37, (uint32)irq5);
    IDTSetGate(38, (uint32)irq6);
    IDTSetGate(39, (uint32)irq7);
    IDTSetGate(40, (uint32)irq8);
    IDTSetGate(41, (uint32)irq9);
    IDTSetGate(42, (uint32)irq10);
    IDTSetGate(43, (uint32)irq11);
    IDTSetGate(44, (uint32)irq12);
    IDTSetGate(45, (uint32)irq13);
    IDTSetGate(46, (uint32)irq14);
    IDTSetGate(47, (uint32)irq15);

    IDTSet(); // Load with ASM

    s_installed = TRUE;
}

bool ISRInstalled() {
    return s_installed;
}
void ISRHandler(ISRRegisters r) {
    TTYSetForeground(TTY_RED);
    TTYSetBackground(TTY_BLACK);
    
    TTYWriteLine("INTERRUPT");
}
void IRQHandler(ISRRegisters r) {
    if(r.int_no >= 40) PortWriteUInt8(0xA0, 0x20);
    PortWriteUInt8(0x20, 0x20);

    if(interrupt_handlers[r.int_no] != 0) {
        ISRCallback handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}

void ISRRegisterInterruptHandler(uint8 n, ISRCallback handler) {
    interrupt_handlers[n] = handler;
}