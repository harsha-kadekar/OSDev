#include "timer.h"

unsigned long timer_ticks = 0;
int seconds = 0;

void timer_phase(int hz)
{
	unsigned int divisor = 0;

	if(hz > 0 )
	{
		//puts("\nInstalling timer\n");
		divisor = 1193180/hz;
		outb(TIMER_COMMAND_PORT, 0x36);
		outb(TIMER_CHANNEL_0_PORT, divisor & 0xFF);
		outb(TIMER_CHANNEL_0_PORT, (divisor >> 8) & 0xFF);
		//puts("\nDone Installing\n");
	}
}

void timer_handler(struct cpu_stack_state state)
{
	int n = 0;
	timer_ticks++;	
	//puts("\nEntered timer handler\n");
	if(timer_ticks % 54 == 0)
	{
		seconds++;
		if (seconds == 60)
		{
			puts("\n1 minute over\n");
			seconds = 0;
		}
	}
	n++;
	n += state.interrupt_no;
}

void install_timer()
{
	timer_phase(50);
	install_irq_handler(0, timer_handler);
}

/*int get_timer_tick_in_sec()
{
	return (timer_ticks/18);
}*/
