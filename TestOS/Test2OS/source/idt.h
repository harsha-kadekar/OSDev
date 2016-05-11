#ifndef IDT_H
#define IDT_H

#include "io.h"

/*
This file hs different structures which deals with interrupts. it also has constants which is needed for the interrupts.
*/

//PIC ports
#define PIC1_PORT 0x20
#define PIC2_PORT 0xA0

//Remapping PIC interrupts
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT PIC2_START_INTERRUPT + 7

#define PIC_ACK 0x20

struct cpu_stack_state
{
	//unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, edx, ecx, ebx, eax, esp;
	unsigned int interrupt_no, error_code;
	unsigned int eip, cs, eflags, useresp, ss;
}__attribute__((packed));

/*
This gives each entry in the Interrupt Descriptor table.
*/
struct idt_entry
{
	unsigned short base_low;
	unsigned short selector;
	unsigned char always0;
	unsigned char flag;
	unsigned short base_hi;
}__attribute__((packed));

/*
This is the structure of the IDTR - Interrupt Descriptor Table Register.
It has two parts
1. base - Base address of the Interrupt Descriptor table. Usually it will be created in physical memory and 0th byte address of that table will be stored here. It is 32 bits in size
2. limit - This gives the total size of the Interrupt Descriptor table. Its size if 16 bits.
*/
struct idt_loader
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

//extern struct idt_entry idt_table;
extern struct idt_loader idt_ptr;

extern void idt_load();

extern void interrupt_handler_0();
extern void interrupt_handler_1();
extern void interrupt_handler_2();
extern void interrupt_handler_3();
extern void interrupt_handler_4();
extern void interrupt_handler_5();
extern void interrupt_handler_6();
extern void interrupt_handler_7();
extern void interrupt_handler_8();
extern void interrupt_handler_9();
extern void interrupt_handler_10();
extern void interrupt_handler_11();
extern void interrupt_handler_12();
extern void interrupt_handler_13();
extern void interrupt_handler_14();
extern void interrupt_handler_15();
extern void interrupt_handler_16();
extern void interrupt_handler_17();
extern void interrupt_handler_18();
extern void interrupt_handler_19();
extern void interrupt_handler_20();
extern void interrupt_handler_21();
extern void interrupt_handler_22();
extern void interrupt_handler_23();
extern void interrupt_handler_24();
extern void interrupt_handler_25();
extern void interrupt_handler_26();
extern void interrupt_handler_27();
extern void interrupt_handler_28();
extern void interrupt_handler_29();
extern void interrupt_handler_30();
extern void interrupt_handler_31();

extern void interrupt_request_0();
extern void interrupt_request_1();
extern void interrupt_request_2();
extern void interrupt_request_3();
extern void interrupt_request_4();
extern void interrupt_request_5();
extern void interrupt_request_6();
extern void interrupt_request_7();
extern void interrupt_request_8();
extern void interrupt_request_9();
extern void interrupt_request_10();
extern void interrupt_request_11();
extern void interrupt_request_12();
extern void interrupt_request_13();
extern void interrupt_request_14();
extern void interrupt_request_15();


void init_idt_descriptor_table();
void interrupt_handler_service(struct cpu_stack_state state);
void idt_set_gate(unsigned int index, unsigned int base, unsigned short select, unsigned char flagvalue);
void interrupt_request_handler(struct cpu_stack_state state);

void pic_acknowledge(unsigned int interrupt);
void remap_irq();
void uninstall_irq_handler(unsigned int index);
void install_irq_handler(unsigned int index, void (*irqHandler)(struct cpu_stack_state));
#endif
