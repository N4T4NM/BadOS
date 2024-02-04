#ifndef TIMER_H
#define TIMER_H

#include <types.h>

typedef void (*TickCallback)();

void TimerSetRate(uint32 freq);
void TimerSetCallback(TickCallback pCallback);
#endif