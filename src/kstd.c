#include <kernel/kstd.h>

static bool s_sti;
bool KernelInterruptsEnabled() {
    return s_sti;
}
void KernelEnableInterrupts() {
    asm volatile("sti");
    s_sti = TRUE;
}