#include "idt.h"

struct idt_entry idt_table[256];
struct idt_loader idt_ptr;

const char *interrupt_service_message[] = {
	"0 - Division by zero exception",
	"1 - Debug Exception",
	"2 - Non maskable interrupt",
	"3 - Breakpoint exception",
	"4 - Into detected overflow",
	"5 - Out of Bounds exception",
	"6 - Invalid opcode exception",
	"7 - No coprocessor exception",
	"8 - Double fault",
	"9 - Coprocessor segment overrun",
	"10 - Bad TSS",
	"11 - segment not present",
	"12 - Stack fault",
	"13 - General protection fault",
	"14 - Page fault",
	"15 - Unkown interrupt exception",
	"16 - Coprocessor fault",
	"17 - Alignment check exception",
	"18 - Machine check exception",
	"19 - Reserved",
	"20 - Reserved",
	"21 - Reserved",
	"22 - Reserved",
	"23 - Reserved",
	"24 - Reserved",
	"25 - Reserved",
	"26 - Reserved",
	"27 - Reserved",
	"28 - Reserved",
	"29 - Reserved",
	"30 - Reserved",
	"31 - Reserved"
};

void *irq_handlers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

void install_irq_handler(unsigned int index, void (*irqHandler)(struct cpu_stack_state))
{
	//puts("\nInstalling handler\n");
	//struct cpu_stack_state ex;
	irq_handlers[index] = irqHandler;
	//irqHandler(ex);
}

void uninstall_irq_handler(unsigned int index)
{
	irq_handlers[index] = 0;
}

void remap_irq()
{
	//outb(0x21,0xfd);
   	//outb(0xa1,0xff);
	outb(0x20, 0x11);
  	outb(0xA0, 0x11);
  	outb(0x21, 0x20);
  	outb(0xA1, 0x28);
  	outb(0x21, 0x04);
  	outb(0xA1, 0x02);
  	outb(0x21, 0x01);
  	outb(0xA1, 0x01);
  	outb(0x21, 0x0);
  	outb(0xA1, 0x0);
	//outb(0x21,0xfd);
   	//outb(0xa1,0xff);
}

void init_idt_descriptor_table()
{
	idt_ptr.limit = (sizeof(struct idt_entry) * 256) - 1;
	idt_ptr.base = (unsigned int)&idt_table;

	idt_set_gate(0, (unsigned int)interrupt_handler_0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned int)interrupt_handler_1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned int)interrupt_handler_2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned int)interrupt_handler_3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned int)interrupt_handler_4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned int)interrupt_handler_5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned int)interrupt_handler_6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned int)interrupt_handler_7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned int)interrupt_handler_8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned int)interrupt_handler_9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned int)interrupt_handler_10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned int)interrupt_handler_11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned int)interrupt_handler_12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned int)interrupt_handler_13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned int)interrupt_handler_14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned int)interrupt_handler_15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned int)interrupt_handler_16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned int)interrupt_handler_17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned int)interrupt_handler_18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned int)interrupt_handler_19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned int)interrupt_handler_20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned int)interrupt_handler_21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned int)interrupt_handler_22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned int)interrupt_handler_23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned int)interrupt_handler_24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned int)interrupt_handler_25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned int)interrupt_handler_26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned int)interrupt_handler_27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned int)interrupt_handler_28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned int)interrupt_handler_29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned int)interrupt_handler_30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned int)interrupt_handler_31, 0x08, 0x8E);

	remap_irq();

	idt_set_gate(32, (unsigned int)interrupt_request_0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned int)interrupt_request_1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned int)interrupt_request_2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned int)interrupt_request_3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned int)interrupt_request_4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned int)interrupt_request_5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned int)interrupt_request_6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned int)interrupt_request_7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned int)interrupt_request_8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned int)interrupt_request_9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned int)interrupt_request_10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned int)interrupt_request_11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned int)interrupt_request_12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned int)interrupt_request_13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned int)interrupt_request_14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned int)interrupt_request_15, 0x08, 0x8E);

	idt_load();

		__asm__ __volatile__ ("sti");
}

void idt_set_gate(unsigned int index, unsigned int base, unsigned short select, unsigned char flagvalue)
{
	idt_table[index].base_low = base & 0xFFFF;
	idt_table[index].selector = select;
	idt_table[index].always0 = 0;
	idt_table[index].flag = flagvalue;
	idt_table[index].base_hi = (base >> 16) & 0xFFFF;
}


void interrupt_handler_service(struct cpu_stack_state state)
{
	puts("\nEntered interrupt handler service\n");
	//putchar(state.interrupt_no);
	puts(interrupt_service_message[state.interrupt_no]);
	
	puts("\nLeaving interrupt handler service\n");
	//for(;;);

}

void interrupt_request_handler(struct cpu_stack_state state)
{
	void (*irqHandler)(struct cpu_stack_state);

	//puts("\nEntered interrupt request handler\n");
	
	irqHandler = irq_handlers[state.interrupt_no - 32];

	if(irqHandler != 0)
	{
		irqHandler(state);
	}

	pic_acknowledge(state.interrupt_no);
		
}


/*
Name: pic_acknowledge
Description: This function will acknowledge an interrupt generated by PIC
Parameters: interrupt number generated
ReturnValue:	-
*/
void pic_acknowledge(unsigned int interrupt)
{
	if(interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT)
	{
		return;
	}

	if(interrupt < PIC2_START_INTERRUPT)
	{
		outb(PIC1_PORT, PIC_ACK);
	}
	else
	{
		outb(PIC2_PORT, PIC_ACK);
	}
}

