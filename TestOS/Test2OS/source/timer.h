#ifndef timer_h
#define timer_h

#include "io.h"
#include "idt.h"

#define TIMER_COMMAND_PORT 0x43
#define TIMER_CHANNEL_0_PORT 0x40
#define TIMER_CHANNEL_1_PORT 0x41
#define TIMER_CHANNEL_2_PORT 0x42

void timer_phase(int hz);
void timer_handler(struct cpu_stack_state state);
void install_timer();
//int get_timer_tick_in_sec();

#endif
