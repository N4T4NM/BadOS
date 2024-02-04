#ifndef IDT_H
#define IDT_H

#include <types.h>

#define KERNEL_CS 0x08

typedef struct {
    uint16 low_offset;
    uint16 sel;
    uint8 always0;
    uint8 flags; 
    uint16 high_offset;
} __attribute__((packed)) IDTGate;

typedef struct {
    uint16 limit;
    uint32 base;
} __attribute__((packed)) IDTRegister;

#define IDT_ENTRIES 256

void IDTSetGate(int32 n, uint32 handler);
void IDTSet();

#endif