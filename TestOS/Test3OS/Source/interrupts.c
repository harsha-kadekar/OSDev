/*****************************************************************************************************************************************************************************************************************************
* Name: interrupts.c
* Description: This file has functions that will handle interrupts. Also it will initialize the interrupt descriptor table, and handling PIC
* References: https://littleosbook.github.io/#interrupts-and-input
*	      http://www.osdever.net/tutorials/view/brans-kernel-development-tutorial
* Date: 8/6/2016
*****************************************************************************************************************************************************************************************************************************/

#include "interrupts.h"
#include "iodisplay.h"

struct idt_ptr idtptr;
struct idt_table_entry idt[256];

char *interrupt_messags[] = {
	"Division by 0 - 0              \n",
	"Debug Exception - 1            \n",
	"Non maskable interrupt - 2     \n",
	"Breakpoint - 3                 \n",
	"Overflow - 4                   \n",
	"Out of bounds - 5              \n",
	"Invalid opcode - 6             \n",
	"No coprocessor - 7             \n",
	"Double fault - 8               \n",
	"Coprocessor segment overrun - 9\n",
	"Bad TSS - 10                   \n",
	"Segment not present - 11       \n",
	"stack fault - 12               \n",
	"General protection fault - 13  \n",
	"Page fault - 14                \n",
	"Unkown interrupt - 15          \n",
	"Coprocessor fault - 16         \n",
	"Alignment check - 17           \n",
	"machine check - 18             \n",
	"reserved - 19                  \n",
	"reserved - 20                  \n",
	"reserved - 21                  \n",
	"reserved - 22                  \n",
	"reserved - 23                  \n",
	"reserved - 24                  \n",
	"reserved - 25                  \n",
	"reserved - 26                  \n",
	"reserved - 27                  \n",
	"reserved - 28                  \n",
	"reserved - 29                  \n",
	"reserved - 30                  \n",
	"reserved - 31                  \n"
};

// Name: initialize_idt
// Description: This function will create interrupt descript table and loads it to IDTR
// Parameters: - 
// Return: - 
void initialize_idt()
{
	struct idt_table_entry nullEntry, entry;
	struct idt_descriptor descript;
	int i = 0;
	nullEntry = idtDescriptorToidtEntry(getidtDescriptor(0,0,0,0,0,0,0,0,0));

	for(i = 0; i < 255; i++)
		idt[i] = nullEntry;

	descript = getidtDescriptor(0x08, (unsigned int)interrupt_handler_0, 1, 1, 0, 0, 0,6, 0 );
	entry = idtDescriptorToidtEntry(descript);
	idt[0] = entry;
	idt[1] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_1, 1, 1, 0, 0, 0,6, 0 ));
	idt[2] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_2, 1, 1, 0, 0, 0,6, 0 ));
	idt[3] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_3, 1, 1, 0, 0, 0,6, 0 ));
	idt[4] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_4, 1, 1, 0, 0, 0,6, 0 ));
	idt[5] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_5, 1, 1, 0, 0, 0,6, 0 ));
	idt[6] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_6, 1, 1, 0, 0, 0,6, 0 ));
	idt[7] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_7, 1, 1, 0, 0, 0,6, 0 ));
	idt[8] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_8, 1, 1, 0, 0, 0,6, 0 ));
	idt[9] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_9, 1, 1, 0, 0, 0,6, 0 ));
	idt[10] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_10, 1, 1, 0, 0, 0,6, 0 ));
	idt[11] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_11, 1, 1, 0, 0, 0,6, 0 ));
	idt[12] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_12, 1, 1, 0, 0, 0,6, 0 ));
	idt[13] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_13, 1, 1, 0, 0, 0,6, 0 ));
	idt[14] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_14, 1, 1, 0, 0, 0,6, 0 ));
	idt[15] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_15, 1, 1, 0, 0, 0,6, 0 ));
	idt[16] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_16, 1, 1, 0, 0, 0,6, 0 ));
	idt[17] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_17, 1, 1, 0, 0, 0,6, 0 ));
	idt[18] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_18, 1, 1, 0, 0, 0,6, 0 ));
	idt[19] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_19, 1, 1, 0, 0, 0,6, 0 ));
	idt[20] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_20, 1, 1, 0, 0, 0,6, 0 ));
	idt[21] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_21, 1, 1, 0, 0, 0,6, 0 ));
	idt[22] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_22, 1, 1, 0, 0, 0,6, 0 ));
	idt[23] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_23, 1, 1, 0, 0, 0,6, 0 ));
	idt[24] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_24, 1, 1, 0, 0, 0,6, 0 ));
	idt[25] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_25, 1, 1, 0, 0, 0,6, 0 ));
	idt[26] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_26, 1, 1, 0, 0, 0,6, 0 ));
	idt[27] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_27, 1, 1, 0, 0, 0,6, 0 ));
	idt[28] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_28, 1, 1, 0, 0, 0,6, 0 ));
	idt[29] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_29, 1, 1, 0, 0, 0,6, 0 ));
	idt[30] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_30, 1, 1, 0, 0, 0,6, 0 ));
	idt[31] = idtDescriptorToidtEntry(getidtDescriptor(0x08, (unsigned int)interrupt_handler_31, 1, 1, 0, 0, 0,6, 0 ));


}



// Name: idtDescriptorToidtEntry
// Description: This function will convert the given idt descriptor to encoded idt entry
// Parameter: descript - the detailed idt descriptor
// Return: encoded idt table entry
struct idt_table_entry idtDescriptorToidtEntry(struct idt_descriptor descript)
{
	struct idt_table_entry entry;

	entry.lower_32_entry = 0;
	entry.upper_32_entry = 0;

	entry.lower_32_entry = descript.segment_selector;
	entry.lower_32_entry = (entry.lower_32_entry << 16);
	entry.lower_32_entry = (entry.lower_32_entry | (descript.lower_offset & 0x0000FFFF));
	entry.upper_32_entry = descript.upper_offset;
	entry.upper_32_entry = (entry.upper_32_entry << 16);
	entry.upper_32_entry = entry.upper_32_entry | ((descript.p & 0x00000001) << 15);
	entry.upper_32_entry = entry.upper_32_entry | ((descript.dpl & 0x00000003) << 13);
	entry.upper_32_entry = entry.upper_32_entry | ((descript.d & 0x00000001) << 11);
	entry.upper_32_entry = entry.upper_32_entry | ((descript.twelthbit & 0x00000001) << 12);
	entry.upper_32_entry = entry.upper_32_entry | ((descript.com3bits_2 & 0x00000007) << 8);
	entry.upper_32_entry = entry.upper_32_entry | ((descript.com3bits_1 & 0x00000007) << 5);
	entry.upper_32_entry = entry.upper_32_entry | (descript.reserved & 0x0000001F);

	return entry;
}

// Name: idtEntryToidtDescriptor
// Description: This function will convert the given encoded idt table entry to detailed descriptor
// Parameter: entry - encoded IDT table entry
// Return: A detailed information of IDT Descriptor
struct idt_descriptor idtEntryToidtDescriptor(struct idt_table_entry entry)
{
	struct idt_descriptor descript;

	descript.segment_selector = (entry.lower_32_entry & 0xFFFF0000) >> 16;
	descript.lower_offset = (entry.lower_32_entry & 0x0000FFFF);
	descript.upper_offset = (entry.upper_32_entry & 0xFFFF0000) >> 16;
	descript.p = (entry.upper_32_entry & 0x00008000) >> 15;
	descript.dpl = (entry.upper_32_entry & 0x00006000) >> 13;
	descript.d = (entry.upper_32_entry & 0x00000800) >> 11;
	descript.twelthbit = 0;
	descript.reserved = 0;
	descript.com3bits_1 = 0;
	descript.com3bits_2 = 7;

	return descript;
}

// Name: getidtDescriptor
// Description: This function will form a detailed IDT descriptor from the given parameters
//		upper 32 bits of IDT: 31-16 - offset(31:16), 15 - p, 14-13 - DPL, 12 - 0, 11 - D, 10-8 - common 2, 7-5 - common 1, 4-0 - reserved
//		lower 32 bits of IDT: 31-16 - Segment selector, 15-0 - offset(15:0)
// Parameter: segSelector - Segment selector indicating an entry in GDT
//	      offset - address to interrupt service routine
//	      p - preset in memory(1) or not(0)
//	      dpl - descriptor priviledge level 0,1,2,3
//	      d - 0 for 16 bits 1 for 32 bits , for task gate it is 0
//	      reserved - will 0
//	      common1 - for Trap Gate it is 0, for interrupt Gate it is 0 and for task gate is reserved.
//	      common2 - for Trap Gate it is 7, for interrupt Gate it is 6, for task gate it is 5
//	      onebit - it is the 12th bit and always 0
// Return: detailed idt descriptor structure.
struct idt_descriptor getidtDescriptor(unsigned short segSelector, unsigned int offset, unsigned char p, unsigned char d, unsigned char reserved, unsigned char dpl, unsigned char common1, unsigned char common2, unsigned char onebit)
{
	struct idt_descriptor descript;
	
	descript.segment_selector = segSelector;
	descript.lower_offset = offset & 0x0000FFFF;
	descript.upper_offset = (offset & 0xFFFF0000) >> 16;
	descript.p = p;
	descript.d = d;
	descript.dpl = dpl;
	descript.twelthbit = onebit;
	descript.com3bits_1 = common1;
	descript.com3bits_2 = common2;
	descript.reserved = reserved;

	return descript;
}

// Name: interrupt_handler
// Description: This is a general interrupt handler which will be called from assembly code for every interrupt
// Parameter: state - saved cpu state like all the registry values and then stack information at that point
// Return: - 
void interrupt_handler(struct cpu_stack_state state)
{
	puts("Enterred interrupt handler\n", 27 );
	
	//putc(state.interrupt_no+'0');

	puts(interrupt_messags[state.interrupt_no], 32);

	puts("Leaving interrupt handler\n", 26);
}



