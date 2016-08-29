/***********************************************************************************************************************************************************************************************************
* Name: keyboard_driver.c
* Description: This file has all the methods for working of a keyboard
* references: http://www.osdever.net/tutorials/view/brans-kernel-development-tutorial
*	      https://littleosbook.github.io/#reading-input-from-the-keyboard
* Date: 8/28/2016
***********************************************************************************************************************************************************************************************************/

#include "iodisplay.h"
#include "interrupts.h"
#include "keyboard_driver.h"

unsigned char scancodetoascii[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',0, '\\', 
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 
};

// Name: keyboardinterrupthandler
// Description: This function will be called whenever a keyboard key is pressed. Get the scancode and decode.
// Parameters: state - CPU and Stack state or contents when the key was pressed or interrput was raised
// Return: -
void keyboardinterrupthandler(struct cpu_stack_state state)
{
	UNUSED(state);
	int nScancode = inb(KEYBOARD_DATA_PORT);
	
	if(nScancode & 0x80)
	{
		//User has pressed control or shift, alt or capslock, etc
		//Handle it based on that
	}
	else
	{
		putc(scancodetoascii[nScancode]);
	}
}

// Name: install_keyboard_interrupt
// Description: This function will be used to enable the keyboard interrupt but assigning irq 1
// Parameters: - 
// Return: -
void install_keyboard_interrupt()
{
	install_irq_handler(1, keyboardinterrupthandler);
}

// Name: remove_keyboard_interrupt()
// Description: This will disable or clear the irq 1, thus removing the keyboard interrupt
// Parameters: - 
// Return: - 
void remove_keyboard_interrupt()
{
	uninstall_irq_handler(1);
}




