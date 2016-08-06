/*********************************************************************************************************************************************************************************************************
* Name: memory_main.c
* Description: This file will have all the functions necessary for implementing paging and segmentation
* References: http://www.intel.com/Assets/en_US/PDF/manual/253668.pdf
* 	      https://littleosbook.github.io/#segmentation
* Date: 8/5/2016
*********************************************************************************************************************************************************************************************************/
#include "memory_main.h"
#include "iodisplay.h"

struct descriptor_table_entry global_desc_table[3];
struct gdt_ptr gdptr;


// Name: formSegmentSelector
// Description: This function will form the segement selector given priviledge level, global or local desecriptor, index in the table.
//		15-3 -> index, 2 -> global or local descriptor, 1-0 -> requested priviledgelevel
// Parameter: index - index of the selector in the respective table either global descriptor table or local descriptor table
//	      globallocal - selection to be made from global(0) or local descriptor table(1)
//	      priviledgelevel - requested priviledge level of the code 0,1,2,3 
unsigned short formSegmentSelector(unsigned short index, unsigned short globallocal, unsigned short priviledgelevel)
{
	unsigned short segSelector = 0;
	segSelector = index;
	segSelector = (segSelector << 1) | (0x0001 & globallocal);
	segSelector = (segSelector << 2) | (0x0003 & priviledgelevel);
	return segSelector;
}

// Name: getIndexFromSelector
// Description: This function will get the index present in the selector
// 		15-3 bits represets the index
// Parameter: selector - Segement selector from which we need to extract the index
// Return: index of the table
unsigned short getIndexFromSelector(unsigned short selector)
{
	return (selector & 0xFFF8) >> 3;
}

// Name: isGlobalFromSelector
// Description: This function will tell whether it is a global or local segment
//		bit 2 represent global/local
// Parameter: selector - segment selector from which we are extracting information.
// Return: 0 for global 1 for local
unsigned short isGlobalFromSelector(unsigned short selector)
{
	return (selector & 0x0004) >> 2;
}

// Name: privilidgeFromSelector
// Description: This function will tell what is the requested priviledge level of the segment selector.
//		1-0 bit represent the priviledge level
// Parameter: selector - segment selector whose priviledge level we are determining
// Return: priviledge level 3,2,1 or 0
unsigned short priviledgeFromSelector(unsigned short selector)
{
	return (selector & 0x0003);
}

// Name: tableEntrytodescriptor
// Description: This function converts the encoded descriptor table entry to actual values
//		0-7 - baseaddress(23:16), 8-11 - Type, 12 - S, 13-14 - DPL, 15 - P, 16-19 - Segment limit(19:16), 20 - AVL, 21 - L, 22 - DB, 23 - G, 24-31 - Base(31:24) 
// 		0-15 - base(15:0), 16-31 - Segment limit (15:0)
// Parameter: entry - encoded descriptor table entry
// Return: decoded descriptor table entry
struct descriptor tableEntrytodescriptor(struct descriptor_table_entry entry)
{
	struct descriptor descript;

	descript.lower_baseaddress = (entry.lower_32_entry & 0xFFFF0000) >> 16;
	descript.lower_limit = (entry.lower_32_entry & 0x0000FFFF);
	descript.upper_baseaddress_1 = (entry.upper_32_entry & 0x000000FF);
	descript.upper_baseaddress_2 = (entry.upper_32_entry & 0xFF000000) >> 24;
	descript.upper_limit = (entry.upper_32_entry & 0x000F0000) >> 16;
	descript.segment_type = (entry.upper_32_entry & 0x00000F00) >> 8;
	descript.descript_type = (entry.upper_32_entry & 0x00001000) >> 12;
	descript.dpl = (entry.upper_32_entry & 0x00006000) >> 13;
	descript.p_segpresent = (entry.upper_32_entry & 0x00008000) >> 15;
	descript.avl = (entry.upper_32_entry & 0x00100000) >> 20 ;
	descript.l64bitmode = (entry.upper_32_entry & 0x00200000 ) >> 21;
	descript.db = (entry.upper_32_entry & 0x00400000) >> 22;
	descript.granularity = (entry.upper_32_entry & 0x00800000) >> 23;

	return descript;
}

//Name: descriptortableentry
//Description: This function converts the detailed descriptor to encoded descriptor table entry
//		0-7 - baseaddress(23:16), 8-11 - Type, 12 - S, 13-14 - DPL, 15 - P, 16-19 - Segment limit(19:16), 20 - AVL, 21 - L, 22 - DB, 23 - G, 24-31 - Base(31:24) 
// 		0-15 - base(15:0), 16-31 - Segment limit (15:0)
// Parameter: descript - a detailed descriptor information
// Return: encoded value for descriptor table entry.
struct descriptor_table_entry descriptortotableentry(struct descriptor descript)
{
	struct descriptor_table_entry entry;
	entry.lower_32_entry = 0;
	entry.upper_32_entry = 0;

	entry.lower_32_entry = descript.lower_baseaddress;
	entry.lower_32_entry = (entry.lower_32_entry << 16 );
	entry.lower_32_entry = (entry.lower_32_entry | (0x0000FFFF & descript.lower_limit));

	entry.upper_32_entry = descript.upper_baseaddress_2;
	entry.upper_32_entry = entry.upper_32_entry << 24;
	entry.upper_32_entry = entry.upper_32_entry |((descript.granularity & 0x00000001) << 23);
	entry.upper_32_entry = entry.upper_32_entry |((descript.db & 0x00000001) << 22);
	entry.upper_32_entry = entry.upper_32_entry |((descript.l64bitmode & 0x00000001) << 21);
	entry.upper_32_entry = entry.upper_32_entry |((descript.avl & 0x00000001) << 20);
	entry.upper_32_entry = entry.upper_32_entry |((descript.upper_limit & 0x0000000F) << 16);
	entry.upper_32_entry = entry.upper_32_entry |((descript.p_segpresent & 0x00000001) << 15);
	entry.upper_32_entry = entry.upper_32_entry |((descript.dpl & 0x00000003) << 13);
	entry.upper_32_entry = entry.upper_32_entry |((descript.descript_type & 0x00000001) << 12);
	entry.upper_32_entry = entry.upper_32_entry |((descript.segment_type & 0x0000000F) << 8);
	entry.upper_32_entry = (entry.upper_32_entry | (0x000000FF & descript.upper_baseaddress_1));
		

	return entry;
}

// Name: getDescriptor
// Description: Given different parameters of a descriptor table entry it will form the descriptor structure and return
// Parameter: base - base address of the segment 32 bits
//            limit - size or limit of the segment 20 bits
//	      type - indicates segment or gate type and specifies kinds of access allowed for this segment and also the growth of the segment
//			code segment = 8 - execute only, 9 - execute only & accessed, 10 - execute or read, 11 - execute or read and accessed, 12 - execute and conforming, 13 - execute confirming accessed, 14 - execute or read conforming, 15 - execute or read conforming accessed
//			data segment = 0 - read, 1 - read and accessed, 2 - read or write, 3 - read or write accessed, 4 - read expand, 5 - read expand accessed, 6 - read or write expand, 7 - read or write expand accessed
//	      granual - scaling of segment limit field. 0 - in bytes, 1 - in 4kbytes
//	      avl - available and reserved bit used for system software.
//	      dpl - priviledge level of segment 0,1,2,3
//	      s - whether it is a system segment(0) or code-data segment(1)
//	      db - interpreted in different way for different types of segment for 32 bits always set to 1, for 16 bit set to 0
//	      l - if set indicates that code is 64 bit
//	      p - indicates if segment is present in memory(1) or not.
struct descriptor getDescriptor(unsigned int base, unsigned int limit, unsigned char type, unsigned char granul, unsigned char avl, unsigned char dpl, unsigned char s, unsigned char db, unsigned char l, unsigned char p)
{
	struct descriptor descript;
	
	descript.segment_type = type;
	descript.granularity = granul;
	descript.descript_type = s;
	descript.l64bitmode = l;
	descript.dpl = dpl;
	descript.avl = avl;
	descript.db = db;
	descript.p_segpresent = p;

	descript.lower_baseaddress = (base & 0x0000FFFF);
	descript.lower_limit = (limit & 0x0000FFFF);
	descript.upper_limit = (limit & 0x000F0000) >> 16;
	descript.upper_baseaddress_1 = (base & 0x00FF0000) >> 16;
	descript.upper_baseaddress_2 = (base & 0xFF000000) >> 24;

	return descript;
}

// Name: initialize_gdt
// Description: This function will create the global descriptor table and then loads the GDTR
// Parameter: -
// Return: - 
void initialize_gdt()
{

	struct descriptor null_entry, cs_entry, ds_entry;
	gdptr.base_address = (unsigned int)&global_desc_table;
	gdptr.size =(unsigned short int) sizeof(struct descriptor_table_entry)*3 - 1;	

	

	null_entry = getDescriptor(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	global_desc_table[0] = descriptortotableentry(null_entry);
	cs_entry = getDescriptor(0, 0xFFFFFFFF, 10, 1, 0, 0, 1, 1, 0, 1 );
	global_desc_table[1] = descriptortotableentry(cs_entry);
	ds_entry = getDescriptor(0, 0xFFFFFFFF, 2, 1, 0, 0, 1, 1, 0, 1 );
	global_desc_table[2] = descriptortotableentry(ds_entry);

	//putc('x');

	load_gdt();

	return;
}

