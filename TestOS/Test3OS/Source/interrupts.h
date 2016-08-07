#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// Name: load_idt
// Description: This function will load the interrupt descriptor table  to the IDTR register. 
//		It uses idtptr variable for doing this.
// Parameters: -
// Return: -
void load_idt();

struct idt_table_entry
{
	unsigned int lower_32_entry;
	unsigned int upper_32_entry;
}__attribute__((packed));

struct idt_descriptor
{
	unsigned short int segment_selector;
	unsigned short int lower_offset;
	unsigned short int upper_offset;
	unsigned char p;
	unsigned char dpl;
	unsigned char d;
	unsigned char twelthbit;
	unsigned char reserved;
	unsigned char com3bits_1;
	unsigned char com3bits_2;
};

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));


struct cpu_stack_state
{
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int edx;
	unsigned int ecx;
	unsigned int ebx;
	unsigned int eax;
	unsigned int esp;
	unsigned int interrupt_no;
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
	unsigned int userresp;
	unsigned int ss;
	
}__attribute__((packed));

void interrupt_handler(struct cpu_stack_state);

void interrupt_handler_0();
void interrupt_handler_1();
void interrupt_handler_2();
void interrupt_handler_3();
void interrupt_handler_4();
void interrupt_handler_5();
void interrupt_handler_6();
void interrupt_handler_7();
void interrupt_handler_8();
void interrupt_handler_9();
void interrupt_handler_10();
void interrupt_handler_11();
void interrupt_handler_12();
void interrupt_handler_13();
void interrupt_handler_14();
void interrupt_handler_15();
void interrupt_handler_16();
void interrupt_handler_17();
void interrupt_handler_18();
void interrupt_handler_19();
void interrupt_handler_20();
void interrupt_handler_21();
void interrupt_handler_22();
void interrupt_handler_23();
void interrupt_handler_24();
void interrupt_handler_25();
void interrupt_handler_26();
void interrupt_handler_27();
void interrupt_handler_28();
void interrupt_handler_29();
void interrupt_handler_30();
void interrupt_handler_31();

extern struct idt_ptr idtptr;

void initialize_idt();
struct idt_table_entry idtDescriptorToidtEntry(struct idt_descriptor descript);
struct idt_descriptor idtEntryToidtDescriptor(struct idt_table_entry entry);
struct idt_descriptor getidtDescriptor(unsigned short segSelector, unsigned int offset, unsigned char p, unsigned char d, unsigned char reserved, unsigned char dpl, unsigned char common1, unsigned char common2, unsigned char onebit);

#endif
