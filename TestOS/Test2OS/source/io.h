#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

//Colors
#define FB_BLACK	0
#define FB_BLUE		1
#define FB_GREEN	2
#define FB_CYAN		3
#define FB_RED		4
#define FB_MAGENTA	5
#define	FB_BROWN	6
#define	FB_LIGHT_GREY	7
#define FB_DARK_GREY	8
#define FB_LIGHT_BLUE	9
#define FB_LIGHT_GREEN	10
#define	FB_LIGHT_CYAN	11
#define FB_LIGHT_RED	12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN	14
#define FB_LIGHT_WHITE	15

//I/O ports
#define FB_COMMAND_PORT	0x3D4
#define FB_DATA_PORT	0x3D5


//I/O commands
#define FB_HIGH_BYTE_COMMAND	14
#define	FB_LOW_BYTE_COMMAND	15


#define TAB_SPACE 8

/*
This function is present in assembly languague. It is used to move the 
cursor to actual locations.
*/
extern void outb(unsigned short port, unsigned char data);
extern unsigned char inb(unsigned short port);


void fb_write_cell_char(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_write_cell_data(unsigned int i, unsigned short data);
void fb_write_cell_char_color(unsigned int i, char c, char color_attribute);
unsigned int index_from_x_y(int x_value, int y_value);
void fb_move_cursor(unsigned short pos);
void scroll();
unsigned int puts_length(char* buf, unsigned int length);
void putchar(unsigned char c);
void puts(const char* buf);
void putunsignednumber(unsigned int num);
//void puts_empty();
void set_background_font_color(unsigned char bg_color);
void set_font_color(unsigned char fg_color);
void cls();
void init_video();

#endif
