/***********************************************************************************************************************************************************************************************************
 * Name: kheap.c
 * Description: This file has all the functions which will deal with memory allocations like heap allocations.
 * References: http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html
 * Date: 2/12/2017
***********************************************************************************************************************************************************************************************************/

extern unsigned int end;
unsigned int placement_address = (unsigned int)&end;

unsigned int kmalloc_internal(unsigned int size, int align, unsigned int *physical)
{
	unsigned int temp = placement_address;

	if(align == 1 && (placement_address & 0xFFFFF000))
	{
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}

	if(physical)
	{
		*physical = placement_address;	
	}

	temp = placement_address;
	placement_address += size;
	return temp;
}

unsigned int kmalloc(unsigned int size)
{
	return kmalloc_internal(size, 0, 0);
}

unsigned int kmalloc_aligned(unsigned int size)
{
	return kmalloc_internal(size, 1, 0);
}

unsigned int kmalloc_physical(unsigned int size, unsigned int *physical)
{
	return kmalloc_internal(size, 0, physical);
}

unsigned int kmalloc_physical_aligned(unsigned int size, unsigned int *physical)
{
	return kmalloc_internal(size, 1, physical);
}


