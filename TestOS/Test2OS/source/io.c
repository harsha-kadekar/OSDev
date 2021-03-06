
#include "io.h"

unsigned short *fb = (unsigned short*)0x000B8000;
int csr_x = 0, csr_y = 0;
int font_background_color = 0x03;
int width_of_screen = 80;
int height_of_screen = 25;

/*
|15 14 13 12 | 11 10 9 8 | 7 6 5 4 3 2 1 0|
|   BG	     |   FG      |     ASCII      |
*/


/*
Name: fb_write_cell_char
Description: This function will be used to write a character to frame buffer.
Parameters:	i - The location in the frame buffer
		c - Character to be written to frame buffer
		fg - The foreground color/font color
		bg - Background color
ReturnValue: - 
*/
void fb_write_cell_char(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	unsigned short cell_data = (((bg & 0x0F) << 4) | (fg & 0x0F));
	cell_data = cell_data << 8;
	cell_data = cell_data | c;
	fb[i] = cell_data;
}

/*
Name: fb_write_cell_data
Description: This function will be used to write character with color info to frame buffer
Parameters: i - location of the frame buffer
	    data - containing char, font color and background color
ReturnValue: -
*/
void fb_write_cell_data(unsigned int i, unsigned short data)
{
	fb[i] = data;
}

/*
Name: fb_write_cell_char_color
Description: This function will be used to write character given character and color attribute
Parameters: i - location of the frame buffer
	    c - character to be written
	    color_attribute - background color and font color
ReturnValue: -
*/
void fb_write_cell_char_color(unsigned int i, char c, char color_attribute)
{
	unsigned short cell_data = color_attribute;
	cell_data = cell_data << 8;
	cell_data = cell_data | c;
	fb[i] = cell_data;
}

/*
Name: index_from_x_y
Description: This function given x and y position of cursor, converts into the index of the frame buffer.
Parameters: x_value- x position of the cursor
	    y_value- y position of the cursor
ReturnValue: index of the frame buffer.
*/
unsigned int index_from_x_y(int x_value, int y_value)
{
	int nIndex = 0;
	nIndex = (y_value*width_of_screen) + x_value;
	return nIndex;
}

/*
Name:	fb_move_cursor
Description:	This function will move the cursor of the screen to  potion
Parameters:	pos - position where the screen needs to be moved
ReturnValue: -
*/
void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

/*
Name: scroll
Description: If frame buffer i.e. console has completed all the rows with character then screen will be moved by one row.
Parameters: - 
ReturnValue: -
*/
void scroll()
{
	int i = 0;
	int j = 0;
	int index = 0;
	unsigned short data = 0;

	if(csr_y >= height_of_screen)
	{
		for(i = 0; i < height_of_screen-1; i++)
		{
			for(j = 0; j<width_of_screen; j++)
			{
				index = index_from_x_y(i+1, j);
				data = fb[index];
				index = index_from_x_y(i, j);
				fb_write_cell_data(index, data);
			}
		}
		
		for(i = 0; i < width_of_screen; i++)
			fb_write_cell_char_color(index_from_x_y(height_of_screen-1, i), ' ', font_background_color);

		csr_y = height_of_screen - 1;
	}
	
}

/*
Name: puts_length
Description: This function will put the character string present in the buf to screen. That is prints text in buf to screen
Parameters:	buf - Buffere containing characters to print
		length - Length of the buffere. How many characters
ReturnValue: Number of characters written to screen.
*/
unsigned int puts_length(char* buf, unsigned int length)
{
	unsigned int i = 0;

	if(buf != 0)
	{
		for(i = 0;  i < length; i++)
		{
			putchar(buf[i]);
		}
	}

	return i;
}

/*void puts_empty()
{
	char *MyString = "Harsha";
	int i = 0;
	for(i = 0; i < 6; i++)
		putchar(MyString[i]);
	
	putchar('H');
	putchar('i');
	putchar('!');
}*/

/*
Name: puts
Description: This function will put the string into frame buffer and intern displays a string.
Parameters: buf - Buffer containing the character string
ReturnValue: -
*/
void puts(const char* buf)
{
	int i = 0;
	if(buf != 0)
	{
		while(buf[i] != '\0')
		{
			putchar((unsigned char)buf[i]);
			i++;
		}
	}
}

/*
Name: putchar
Description:	This function will write a character to the console
Parameter: c - character to be written
ReturnValue: -
*/
void putchar(unsigned char c)
{
	
	if(c == 0x08)
	{
		//backspace
		if(csr_x != 0)
		{
			csr_x--;
		}
		//Should we not make the previous character a blank??
	}
	else if(c == 0x09)
	{
		//tab
		csr_x = (csr_x + TAB_SPACE) & (TAB_SPACE - 1);
				
	}
	else if(c == '\r')
	{
		csr_x = 0;
	}
	else if(c == '\n')
	{
		csr_y++;
		csr_x = 0;
	}
	else if(c >= ' ')
	{
		fb_write_cell_char_color(index_from_x_y(csr_x, csr_y), c, font_background_color);
		csr_x++;
	}

	if(csr_x >= width_of_screen)
	{
		csr_x = 0;
		csr_y++;
	}

	scroll();
	fb_move_cursor(index_from_x_y(csr_x, csr_y));

	
}

void putunsignednumber(unsigned int num)
{
	int temp = num;
	int digitCount = 0;
	int i = 0;
	int mul = 1;
	int charact = 0;

	if(num != 0)
	{	
		while(temp>9)
		{
			temp = temp/10;
			digitCount++;
		}
		digitCount++;

		for(i = 0; i < digitCount - 1; i++)
		{
			mul *= 10;
		}
		
		temp = num;
		while(mul > 0 )
		{
			charact = temp / mul;
			putchar(charact + '0');
			temp = temp % mul;
			mul /= 10;
		}
	}
	else
	{
		putchar('0');
	}

		
}


/*
Name: set_background_font_color
Description: This function will change the baground color of the console
Parameters: bg_color - Color to which background needs to be changed.
ReturnValue: -
*/
void set_background_font_color(unsigned char bg_color)
{
	int nfontcolor = 0;
	int nbg_color_mask = 0x0F;

	nfontcolor = font_background_color & nbg_color_mask;
	//nbackgroundcolour = font_background_color & ncolormasker_fg;
	font_background_color = (bg_color << 4) | nfontcolor;	
}

/*
Name: set_font_color
Description: This function will change the font color of the console
Parameters: fg_color - Color to which font color needs to be changed.
ReturnValue: -
*/
void set_font_color(unsigned char fg_color)
{
	int nbg_color = 0;
	
	
	nbg_color = font_background_color >> 4;
	
	font_background_color = (nbg_color << 4) | fg_color;
}

/*
Name: cls
Description: This function is used to clear the screen
Parameteres: -
ReturnValue: -
*/
void cls()
{
	unsigned blank = 0;
	int i = 0;
	int j = 0;
	int index = 0;
	
	blank = 0x20;

	for(i = 0; i < width_of_screen; i++)
	{
		for(j = 0; j<height_of_screen; j++)
		{
			index = index_from_x_y(i, j);
			fb_write_cell_char_color(index, blank, font_background_color);
		}
	}
	
	csr_x = 0;
	csr_y = 0;
	index = index_from_x_y(csr_x, csr_y);
	fb_move_cursor(index);

}

/*
Name: init_video
Description: This function will initialize the video drivers and frame buffers.
Parameters: - 
ReturnValue: -
*/
void init_video()
{
	fb = (unsigned short*)0x000B8000;
	csr_x = 0;
	csr_y = 0;
	font_background_color = 0x03;	//Black background, red font color
	cls();
}


/*
Name: read_scan_code
Description:	This function will read the data present in the data port of the keyboard. It is reading scan code
Parameters: -
ReturnValue: read character - scan code.
*/
//unsigned char read_scan_code()
//{
//	return inb(KBD_DATA_PORT);
//}

