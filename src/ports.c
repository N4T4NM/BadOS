#include <drivers/ports.h>

uint8 PortReadUInt8(uint16 port) { 
    uint8 result;
     __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}
uint16 PortReadUInt16(uint16 port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void PortWriteUInt8(uint16 port, uint8 data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
void PortWriteUInt16(uint16 port, uint16 data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}