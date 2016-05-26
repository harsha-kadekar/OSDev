/* NAME: link.ld */
/* DESCRIPTION: This is the linker script. It links as well as loads the OS at specific locations */
/* DATE: 5-25-2016 */
/* Reference: https://littleosbook.github.io/#first-steps */


ENTRY(loader)					/* the name of the entry label */

SECTIONS {
	. = 0x00100000;				/* Address where the OS needs to be loader. Roughly 1 MB. Remember below 1 MB memory is occupied by the GRUB and BIOS */

	.text ALIGN (0x1000) :			/* align the text section at 4 kB */
	{
		*(.text)			/* all text section from all files */
	}

	.rodata ALIGN (0x1000) :		/* align the read only data section at 4 kB */
	{
		*(.rodata*)			/* all the read only data section from all files */
	}

	.data ALIGN (0x1000) :			/* align the data section at 4 kB */
	{
		*(.data*)			/* all the data section from all files */
	}

	.bss ALIGN (0x1000) :			/* align the bss section at 4 kB */
	{
		*(COMMON)			/* all COMMON sections from all files */
		*(.bss)				/* all bss sections from all files */
	}

}
