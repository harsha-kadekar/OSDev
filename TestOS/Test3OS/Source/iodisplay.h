#ifndef INCLUDE_IODISPLAY_H
#define INCLUDE_IODISPLAY_H


/*
 * Name: outb
 * Description: This function is used to put a character on the display. Basically it will send one byte to IO port.
 *		This function is defined in io.s file. port is the address of the port and data is the actual data which needs to be sent.
 * Parameters: port - Address of the port
 *	       data - actual data to be sent to the port.
 * return: -
*/
void outb(unsigned short port, unsigned char data);

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

#define ADDRESS_FB_BW 0x000B0000
#define ADDRESS_FB_CO 0x000B8000

#define FB_WIDTH 80
#define FB_HEIGHT 25

#define TAB_SPACE 8

#define BLACK_COLOR 0
#define BLUE_COLOR 1
#define GREEN_COLOR 2
#define CYAN_COLOR 3
#define RED_COLOR 4
#define MAGENTA_COLOR 5
#define BROWN_COLOR 6
#define LIGHT_GREY_COLOR 7
#define DARK_GREY_COLOR 8
#define LIGHT_BLUE_COLOR 9
#define LIGHT_GREEN_COLOR 10
#define LIGHT_CYAN_COLOR 11
#define LIGHT_RED_COLOR 12
#define LIGHT_MAGENTA_COLOR 13
#define LIGHT_BROWN_COLOR 14
#define WHITE_COLOR 15

void fb_move_cursor(unsigned short pos);
unsigned short getPositionForFB(int row, int col);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
int putc(char ch);
int puts(char *buf, unsigned int len);
void scroll();
void setbackgroundcolor(unsigned char newBG);
void setforegroundcolor(unsigned char newFG);
void clearscreen();
void init_console();

#endif
