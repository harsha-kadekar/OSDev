#ifndef TIMER_H
#define TIMER_H

#define UNUSED(x) (void)(x)

#define PIT_DATA_PORT_0 0x40
#define PIT_DATA_PORT_1 0x41
#define PIT_DATA_PORT_2 0x42

#define PIT_COMMAND_PORT 0x43

#define TIMER_PHASE 36

void remove_timer_interrupt();
void initialize_timer_interrupt();
void wait_for_ticks(int ticks);
void timerinterrupthandler(struct cpu_stack_state state);
void set_timer_phase(int hz);
void setData(unsigned short port, unsigned short data);
void setCommand(unsigned char counter, unsigned char readwritemode, unsigned char mode, unsigned char bcd);

#endif
