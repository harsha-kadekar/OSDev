/***********************************************************************************************************************************************************************************************************
* Name: timer.c
* Description: This file will have functions related to timer. It will have functions to handle PIT basically to keep count of time.
* Date: 8/19/2016
* References: http://www.osdever.net/tutorials/view/brans-kernel-development-tutorial
*	      http://kernelx.weebly.com/programmable-interval-timer.html
***********************************************************************************************************************************************************************************************************/
#include "iodisplay.h"
#include "interrupts.h"
#include "timer.h"

unsigned long ticker = 0;
int nTick_Counter = 0;
int nSeconds = 0;
int nMinutes = 0;
int nHours = 0;
int nDays = 0;

// Name: setCommand
// Descritpion: This actually writes to PIT_COMMAND_PORT. Here we are actually configuring about the data which is present in the data register.
//		7-6: Couner [0 - Chanel 0, 1 - Chanel 1, 2 - Chanel 2], 5-4: read write mode [0 - only least significant byte, 1 - only most significant byte, 2 - both leas and most signifcant byte],
//		3-1: Mode [0 - Interrupt on terminal count, 1 - hardware retrigerable one shot, 2- rate generator, 3 - square wave mode, 4 - software probe, 5 - hardware probe],
//		0: BCD [ 0 - 16 bit counter, 1 - 4x BCD counter]
// parameters: counter - which channel command is being set
//		readwritemode - data being written is 16 bit or 8 bit and which part of 16 bit data
//		mode - different types of wave generation
//		bcde - counter is 16 bit or bcd counter
// return: -
void setCommand(unsigned char counter, unsigned char readwritemode, unsigned char mode, unsigned char bcd)
{
	unsigned char command = 0;
	
	command = (counter & 0x03) << 6;
	command = ((readwritemode & 0x03) << 4) | command;
	command = ((mode & 0x07) << 1) | command;
	command = ((bcd & 0x01) | command);

	outb(PIT_COMMAND_PORT, command);
	
}

// Name: setData
// Description: This will write data to particular port of PIT
// Parameters: port - which port of PIT where data needs to be written
// 		data - the data to be written to port
// return: - 
void setData(unsigned short port, unsigned short data)
{
	outb(port, data & 0xFF);
	outb(port, data >> 8);
}

// Name: set_timer_phase
// Description: This will set the divisor of the Channel 0 of PIT. Basically it is setting the for how many times a tick will be generated for every second.
// parameter: hz - <<need to understand this properly>>
// return: -
void set_timer_phase(int hz)
{
	short int divisor = 1193180/hz;
	
	setCommand(0, 3, 3, 0);
	setData(PIT_DATA_PORT_0, divisor);
}

// Name: timerinterrupthandler
// Description: This is the interrupt handler called whenever a Timer tick interrupt is raised. It basically keeps count of the time from the point of system start.
// Parameter: state - This is the state of the cpu registers and stack at the point when interrupt was raised
// Return: -
void timerinterrupthandler(struct cpu_stack_state state)
{
	UNUSED(state);
	nTick_Counter++;
	ticker++;

	if((nTick_Counter % 36) == 0 && nTick_Counter != 0)
	{
		nSeconds++;
		nTick_Counter = 0;
	}

	if((nSeconds % 60) == 0 && nSeconds != 0)
	{
		nMinutes++;
		//puts("1 Minute has passed\n", 20);
		nSeconds = 0;
	}

	if((nMinutes % 60) == 0 && nMinutes != 0)
	{
		nHours++;
		nMinutes = 0;
	}

	if((nHours % 24) == 0 && nHours != 0)
	{
		nDays++;
		nHours = 0;
	}
	
}

// Name: wait_for_ticks
// Description: This function will stops/waits for certain number of ticks.
// parameter: ticks - Number of ticks to wait
// return: -
void wait_for_ticks(int ticks)
{
	unsigned long value = ticker + ticks;
	while(ticker < value);
}

// Name: initialize_timer_interrupt
// Description: This function will initialize the timer interrupt and PIT, and then installs the interrupt handler for that interrupt
// parameter: - 
// return: -
void initialize_timer_interrupt()
{
	set_timer_phase(TIMER_PHASE);
	install_irq_handler(0, timerinterrupthandler);
}

// Name: remove_timer_interrupt
// Description: This funciton removes the interrupt handler of timer from idt
// Parameter: - 
// Return: -
void remove_timer_interrupt()
{
	uninstall_irq_handler(0);
}
