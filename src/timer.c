#include <kernel/timer.h>
#include <kernel/isr.h>
#include <drivers/ports.h>
#include <drivers/tty.h>

static TickCallback s_pCallback;
static void TimerCallback(ISRRegisters r) {
    if(s_pCallback) s_pCallback();
}
void TimerSetCallback(TickCallback callback) {
    s_pCallback = callback;
}

void TimerSetRate(uint32 rate) {
    ISRRegisterInterruptHandler(IRQ0, TimerCallback);

    uint32 d = 1193182 / rate;
    uint8 lo = (uint8)(d & 0xFF);
    uint8 hi = (uint8)((d >> 8) & 0xFF);

    PortWriteUInt8(0x43, 0x36);
    PortWriteUInt8(0x40, lo);
    PortWriteUInt8(0x40, hi);
}