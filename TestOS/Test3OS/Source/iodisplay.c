/******************************************************************************************************************************************************
 Name: iodisplay.c
 Description: This file will have all the function related to writing text to the display or framebuffer.
 reference: https://littleosbook.github.io/#interacting-with-the-hardware
	    http://kernelx.weebly.com/text-console.html
	    https://littleosbook.github.io/#the-serial-ports
 Date: 7/24/2016
******************************************************************************************************************************************************/

#include "iodisplay.h"

int curx = 0, cury = 0;				//This is the current position of the cursor in the screen
unsigned short *fb;				//This is the framebuffer
unsigned char currentFG = 0;			//This is the current foreground color of the framebuffer. ie font color of the console
unsigned char currentBG = 0;			//This is the burrent background color of the framebuffer. ie background color of the font.

int log_level = 0;				//This will be used for the logging of the messages to the serial port
int default_serial_port = SERIAL_COM1_BASE;	//This is the serial port where serial_putstring will be writing data to


// Name: fb_move_cursor
// Description: This function will move the cursor of the screen to the desired position.
// parameter: pos - position to where cursor needs to be moved
// return: -
void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8)&0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

// Name: getPositionForFB
// Description: This function will give the position in FB where we need to write the charactr given row and column of FB
// parameter: row - row index of the FB
//	      col - column index of the FB
// return: linear address or position in the FB where data needs to be put
unsigned short getPositionForFB(int row, int col)
{
	unsigned short position = (row * FB_WIDTH) + col;
	return position;
}

// Name: fb_write_cell
// Description: This function will write a character to the framebuffer
// parameter: i - position or index of the framebuffer where the character needs to be written
//	      c - character to be written to the framebuffer
//	      fg - color of the font when written
//	      bg - background color of the character which will be written to framebuffer
// return: -
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	//fb[i] = c;
	fb[i] = c | ((((fg & 0x0F) << 4) | (bg & 0x0F))<<8);
}


// Name: putc
// Description: This function will put one character to the screen or FB
// parameter: ch - character to be printed in the screen
// return: 0 for success else error
int putc(char ch)
{
	int nReturn = 0;
	if(ch == 0x08 && curx)
	{
		//Handling backspace
		curx--;
	}
	else if(ch == 0x09)
	{
		//Handling tab
		curx = (curx + TAB_SPACE) & ~(TAB_SPACE - 1);
	}
	else if(ch == '\r')
	{
		//Handling carriage return - basically we are moving to the beginning of that row
		curx = 0;
	}
	else if(ch == '\n')
	{
		//Handling new line
		curx = 0;
		cury++;
	}
	else
	{
		//Print the character
		fb_write_cell(getPositionForFB(cury, curx), ch, currentFG, currentBG);
		curx++;
	}

	if(curx >= FB_WIDTH)
	{
		//Handle if we have finished that line
		curx = 0;
		cury++;
	}

	scroll();
	fb_move_cursor(getPositionForFB(cury, curx));
	return nReturn;
}

// Name: puts
// Description: This function will put a string of characters to the screen or FB
// parameter: buf - character array to be filled into FB
//	      len - length of the character array
// return: 0 for success else error
int puts(char *buf, unsigned int len)
{
	int nReturn = 0;
	unsigned int i = 0;
	for(i = 0; i < len; i++)
		putc(buf[i]);
	return nReturn;
}


// Name: scroll
// Description: This function will scroll the screen vertically by one line/row
// parameter: - 
// return: -
void scroll()
{
	int index = 0;
	char space = 0x20;
	if(cury >= FB_HEIGHT)
	{
		for(index = 0; index < (FB_HEIGHT - 1)*FB_WIDTH; index++)
		{
			fb[index] = fb[index+FB_WIDTH];
		}

		for(index = (FB_HEIGHT - 1)*FB_WIDTH; index < FB_HEIGHT*FB_WIDTH; index++)
		{
			fb_write_cell(index, space, currentFG, currentBG);
		}
		cury = FB_HEIGHT - 1;
		
	}
}

// Name: setbackgroundcolor
// Description: This function will set the background color of the console
// Parameter: newBG - color code of the new color to be set
// Return: -
void setbackgroundcolor(unsigned char newBG)
{
	currentBG = newBG;
}

// Name: setforegroundcolor
// Description: This function will set the foreground color of the console. Basically it will set the font color
// Parameter: newFG - color code of the new color to be set
// Return: -
void setforegroundcolor(unsigned char newFG)
{
	currentFG = newFG;
}


// Name: clearscreen
// Description: This function will clear the screen of the framebuffer
// parameter: -
// return: -
void clearscreen()
{
	unsigned short space = 0x20;
	int i = 0;

	for(i = 0; i < FB_WIDTH*FB_HEIGHT; i++)
	{
		fb_write_cell(i, space, currentFG, currentBG);
	}
	fb_move_cursor(getPositionForFB(0,0));
	
}

// Name: init_console
// Description: This function initializes the framebuffer or console
// Parameter: - 
// return: - 
void init_console()
{
	fb = (unsigned short *)ADDRESS_FB_CO;
	setbackgroundcolor(WHITE_COLOR);
	setforegroundcolor(BLACK_COLOR);
	clearscreen();
	puts("CONSOLE IS INITIALIZED.\n", 24);
}

// Name: serial_configure_baud_rate
// Description: This function sets the speed of the serail port for future communication.
// Parameters: com - Serial port whose speed is being configured
// 	       divisor - 115200/divisor baud rate
// return: -
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
	outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com), ((divisor >> 8) & 0x00FF));
	outb(SERIAL_DATA_PORT(com), (divisor & 0x00FF));

}

// Name: serial_configure_line
// Description: This sets the type of data which is being transferred throught the port
// 			Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
//			Content: | d | b | prty  | s | dl  |
//			Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
// Parameter: com - serial port whose configuration is being done
// Return: -
void serial_configure_line(unsigned short com)
{
	outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_CONFIGURE);
}

// Name: serial_configure_fifo
// Description: This sets the buffer for the port. 
//		Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
//		Content: | lvl | bs | r | dma | clt | clr | e |
// Parameter: com - serial port whose configuration is being done
// Return: - 
void serial_configure_fifo(unsigned short com)
{
	outb(SERIAL_FIFO_COMMAND_PORT(com), SERIAL_FIFO_CONFIGURE);
}

// Name: serial_configure_modem
// Description: This function indicates that port is ready to send data.
//		Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
//		Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
// Parameter: com - serial port whose configuration is being done
// Return: -
void serial_configure_modem(unsigned short com)
{
	outb(SERIAL_MODEM_COMMAND_PORT(com), SERIAL_MODEM_CONFIGURE);
}

// Name: serial_is_transmit_fifo_empty
// Description: This function tells whether the port buffer is empty of full.
// Parameter: com - serial port whose configuration fifo buffer is checked
// Return: 0 - if the buffer is not empty
//	   1 - if the buffer is empty
int serial_is_transmit_fifo_empty(unsigned short com)
{
	return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20; 
}

// Name: serial_putc
// Description: This function will put a character to the serial port
// Parameters: com - serail port address where we want to write
//	       ch - character to be written to the port
// Return: -
void serial_putc(unsigned short com, char ch)
{
	outb(SERIAL_DATA_PORT(com), ch);
}	

// Name: serial_puts
// Description: This function will put a string to the serial port
// Parameters: com - serail port address
// 	       buf - character array/string to be printed to the serial port
//	       length - length of the string to be written to the serail port
// Return: - 
void serial_puts(unsigned short com, char *buf, int length)
{
	int i = 0;
	

	for(i = 0; i < length; i++)
	{
		
		
		while(serial_is_transmit_fifo_empty(com) == 0)
		{
			
		}
		
		serial_putc(com, buf[i]);	
		
	}
}

// Name: serial_putstring
// Description: This function is the interface to the outside world. Basically it will call the serial_puts with the default serail port
// Parameters: buf - string to be printed to the serial port
// 	       length - length of the string to be written
// Return: - 
void serail_putstring(char *buf, int length)
{
	serial_puts(default_serial_port, buf, length);

}

// Name: log
// Description: This will be used for the logging purpose of the Operating System. It will print based on the set logging level and type of message
// Parameters: msg - logging message to be printed to the serial port
//	       nLength - Length of the logging message
//	       nLevel - type of the logging message - info, warn, debug, error
// Return: - 
void log(char* msg, int nLength, int nLevel)
{
	switch(log_level)
	{
		case LOG_ERROR:
		{
			if(nLevel == LOG_ERROR)
				serail_putstring(msg, nLength);
			break;
		}
		case LOG_WARN:
		{
			if(nLevel >= LOG_WARN)
				serail_putstring(msg, nLength);
			break;
		}
		case LOG_DEBUG:
		{
			if(nLevel >= LOG_DEBUG)
				serail_putstring(msg, nLength);
			break;
		}
		case LOG_INFO:
		{
			if(nLevel >= LOG_INFO)
				serail_putstring(msg, nLength);
			break;
		}
		default:
		{
			serail_putstring(msg, nLength);
			break;
		}
	}

}

// Name: configure_serial_port
// Description: This is the initialization of the serial port. After this we can write to serial port
// Parameter: nLevel - Log level for the operating system will be set here.
// Return: -
void configure_serial_port(int nLevel)
{
	serial_configure_baud_rate(SERIAL_COM1_BASE, 12);
	serial_configure_line(SERIAL_COM1_BASE);
	serial_configure_fifo(SERIAL_COM1_BASE);
	serial_configure_modem(SERIAL_COM1_BASE);

	default_serial_port = SERIAL_COM1_BASE;

	log_level = nLevel;

	
}

