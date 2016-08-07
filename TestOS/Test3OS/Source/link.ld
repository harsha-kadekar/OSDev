/***************************************************************************************************************/
/* Name: link.ld */
/* Description: This file is the linker script. It tells where each sections - text, data, bss has to be loaded*/
/* Reference: http://littleosbook.github.io/#introduction */
/*	      http://wiki.osdev.org/Grub_Error_13 */
/* Date: 6/10/2016 */
/***************************************************************************************************************/

ENTRY(loader)			/* the name of the entry label */

SECTIONS
{
	. = 0x00100000;		/* the code should be loaded at 1 MB */

	.multiboot : {          /* remember multiboot section should be within first 8kb */
		*(.multiboot)
	}
	
	.text ALIGN (0x1000) :	/* align at 4 KB */
	{
		*(.text)	/* all text sections from all files has to be loaded here. */
		*(.rodata)
	}	

	.data ALIGN (0x1000) :	/* align at 4 KB */
	{
		*(.data)	/* all data sections from all files */
	}
	
	.bss ALIGN (0x1000) :	/* align at 4 KB */
	{
		*(COMMON)	/* all COMMON sections from all files */
		*(.bss*)		/* all bss sections from all files */
	}
}
