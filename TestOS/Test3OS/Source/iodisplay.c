/******************************************************************************************************************************************************
 Name: iodisplay.c
 Description: This file will have all the function related to writing text to the display or framebuffer.
 reference: https://littleosbook.github.io/#interacting-with-the-hardware
	    http://kernelx.weebly.com/text-console.html
 Date: 7/24/2016
******************************************************************************************************************************************************/

#include "iodisplay.h"

int curx = 0, cury = 0;				//This is the current position of the cursor in the screen
unsigned short *fb;				//This is the framebuffer
unsigned char currentFG = 0;			//This is the current foreground color of the framebuffer. ie font color of the console
unsigned char currentBG = 0;			//This is the burrent background color of the framebuffer. ie background color of the font.


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



