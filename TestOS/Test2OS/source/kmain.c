#include "io.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"
#include "string_functions.h"
#include "Multiboot.h"

typedef void (*call_module_t)(void);

int kmain(multiboot_info_t *mbinfo)
{
	/*call_module_t start_program = 0;
	
	unsigned int address_of_module = mbinfo->mods_addr;*/
	
	//init_video();
	//init_gdt_descriptor_table();

	call_module_t start_program = 0;
	
	unsigned int address_of_module = mbinfo->mods_addr;

	start_program = (call_module_t)address_of_module;

	//puts("Hi! I am Test2OS. An operating system in the making.");
	

	
	start_program();
	//puts("\nReturning...\n");
	return 0;
}

int main()
{
	
	
	//putchar('S');	
	//int m = 0;
	//int n = 0;
	init_video();
	init_gdt_descriptor_table();
	init_idt_descriptor_table();
	//puts_empty();
	puts("Hi! I am Test2OS. An operating system in the making.");
	install_timer();
	keyboard_install();
	
	

	//puts_length("Hi!", (unsigned int)3);
	//putchar('R');
	//m = 5/n;
	//n = m++;
	
	
	//putchar('A');
	//putchar('R');
	//putchar('S');
	//putchar('H');
	//putchar('A');
	return 0;

}
