/***************************************************************************************************************
 Name: kmain.c
 Description: This is the starting point for the c code of the kernel. This will be called by the loader
 References: http://littleosbook.github.io/#getting-to-c
 Date: 6/10/2016
****************************************************************************************************************/
#include "iodisplay.h"
#include "string_functions.h"
#include "memory_main.h"
#include "interrupts.h"
#include "timer.h"
#include "keyboard_driver.h"
#include "multiboot.h"
#include "common_functions.h"
#include "paging.h"

typedef void (*call_module)(void);

int Nmain(unsigned int ebx)
{
	multiboot_info_t *mbInfo = (multiboot_info_t *)ebx;
	unsigned int address_of_module = mbInfo->mods_addr;

	call_module start_program = (call_module)address_of_module;

	if(mbInfo->mods_count == 1)
	{
		start_program();
		return 0x700BE;
	}
	else
	{
		return 0xCAFEBABE;
	}
}

int newmain(unsigned int ebx)
{
	/*char *test = "asflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;l\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;ljlasfaf\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljs\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nThis is my test string.";
	int nlen = string_length(test);*/
	
	int nLen = 0;
	char *strconsole_init = "************WELCOME TO TEST3OS - by Harsha Kadekar***********\n";
	char *strserial_port_init = "1. Initializing serial port......\n";
	char *strserial_port_initcomp = "\tserial port initialized... log level set to Info\n";
	char *startgdt = "2. Initializing global descriptor table.....\n";
	char *endgdt = "\tglobal descriptor table initialized\n";
	char *startidt = "3. Initializing interrupt descriptor table & PIC.....\n";
	char *endidt = "\tinterrupt descriptor table and PIC initialized\n";
	char *starttimer = "4. Initializing timer interrupt....\n";
	char *endtimer = "\ttimer interrupt installed\n";
	char *startkeyboard = "5. Initializing keyboard interrupt.....\n";
	char *endkeyboard = "\tkeyboard interrupt installed\n";
	char *startpaging = "6. Initializing paging....\n";
	char *endpaging = "\tpaging initialized\n";

	multiboot_info_t *mbInfo = (multiboot_info_t *)ebx;
	unsigned int address_of_module = mbInfo->mods_addr;

	call_module start_program = (call_module)address_of_module;
	UNUSED(start_program);
	

	init_console();
	//puts(test, nlen);
	nLen = string_length(strconsole_init);
	puts(strconsole_init, nLen);
	nLen = string_length(strserial_port_init);
	puts(strserial_port_init, 34 );
	configure_serial_port(LOG_INFO);
	nLen = string_length(strserial_port_initcomp);
	puts(strserial_port_initcomp, 50);
	log(strserial_port_initcomp, 50, LOG_INFO);
	puts(startgdt, 45);
	log(startgdt, 45, LOG_INFO);
	initialize_gdt();
	puts(endgdt,  37);
	log(endgdt, 37, LOG_INFO);

	log(startidt, 54, LOG_INFO);
	puts(startidt, 54);
	initialize_idt();
	log(endidt, 48, LOG_INFO);
	puts(endidt, 48);

	log(starttimer, 36, LOG_INFO);
	puts(starttimer, 36);
	initialize_timer_interrupt();
	log(endtimer, 27, LOG_INFO);
	puts(endtimer, 27);

	log(startkeyboard, 40, LOG_INFO);
	puts(startkeyboard, 40);
	install_keyboard_interrupt();
	log(endkeyboard, 30, LOG_INFO);
	puts(endkeyboard, 30);

	log(startpaging, 27, LOG_INFO);
	puts(startpaging, 27);
	initialize_paging();
	log(endpaging, 20, LOG_INFO);
	puts(endpaging, 20);

	//Uncomment following code to check if page fault is generated or not

	//unsigned int *ptr = (unsigned int*)0xA0000000;
   	//unsigned int do_page_fault = *ptr;

	//do_page_fault++;
	

	//start_program();

	return 0xF00DCAFE;			//Passing this value to verify whether call to main was successfull. after return EAX register should have this value.

}
