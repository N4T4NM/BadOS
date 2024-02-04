#include <clock.h>
#include <kernel/isr.h>
#include <kernel/timer.h>
#include <kernel/kstd.h>

static uint64 s_elapsed;
static void ClockTick() {
    s_elapsed += 1;
}

void InitClock() {
    s_elapsed = 0;

    if(!ISRInstalled()) ISRInstall();
    if(!KernelInterruptsEnabled()) KernelEnableInterrupts();

    TimerSetCallback(ClockTick);
    TimerSetRate(1000);
}

uint64 ClockTimeSinceStartupMs() {
    return s_elapsed;
}