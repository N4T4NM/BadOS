#ifndef PORTS_H
#define PORTS_H

#include <types.h>

uint8 PortReadUInt8(uint16 port);
void PortWriteUInt8(uint16 port, uint8 data);

uint16 PortReadUInt16(uint16 port);
void PortWriteUInt16(uint16 port, uint16 data);

#endif