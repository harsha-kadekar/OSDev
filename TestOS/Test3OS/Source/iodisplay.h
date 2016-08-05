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

/*
 * Name: inb
 * Description: This function is used read the data(byte) from the I/O port mentioned by the port.
 * Parameters: port - Address of the I/O port
 * return: byte data read from the I/O port.
*/
unsigned char inb(unsigned short port);

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

#define SERIAL_COM1_BASE 0x3F8

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

#define SERIAL_LINE_CONFIGURE 0x03
#define SERIAL_FIFO_CONFIGURE 0xc7
#define SERIAL_MODEM_CONFIGURE 0x03

#define LOG_INFO 0
#define LOG_DEBUG 1
#define LOG_WARN 2
#define LOG_ERROR 3

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

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
void serial_configure_fifo(unsigned short com);
void serial_configure_modem(unsigned short com);
int serial_is_transmit_fifo_empty(unsigned short com);
void serial_putc(unsigned short com, char ch);
void serail_putstring(char *buf, int length);
void log(char* msg, int nLength, int nLevel);
void configure_serial_port(int nLevel);

#endif
