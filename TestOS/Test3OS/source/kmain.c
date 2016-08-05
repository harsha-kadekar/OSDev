/***************************************************************************************************************
 Name: kmain.c
 Description: This is the starting point for the c code of the kernel. This will be called by the loader
 References: http://littleosbook.github.io/#getting-to-c
 Date: 6/10/2016
****************************************************************************************************************/
#include "iodisplay.h"
#include "string_functions.h"

int main()
{
	/*char *test = "asflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;l\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;ljlasfaf\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljs\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nThis is my test string.";
	int nlen = string_length(test);*/
	
	int nLen = 0;
	char *strconsole_init = "************WELCOME TO TEST3OS - by Harsha Kadekar***********\n";
	char *strserial_port_init = "1. Initializing serial port......\n";
	char *strserial_port_initcomp = "   serial port initialized... Set the log level to Info\n";

	init_console();
	//puts(test, nlen);
	nLen = string_length(strconsole_init);
	puts(strconsole_init, nLen);
	nLen = string_length(strserial_port_init);
	puts(strserial_port_init, 34 );
	configure_serial_port(LOG_INFO);
	nLen = string_length(strserial_port_initcomp);
	puts(strserial_port_initcomp, 56);
	log(strserial_port_initcomp, 56, LOG_INFO);
	return 0xF00DCAFE;			//Passing this value to verify whether call to main was successfull. after return EAX register should have this value.

}
