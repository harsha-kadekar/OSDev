#ifndef MEMORY_MAIN_H
#define MEMORY_MAIN_H

// Name: load_gdt
// Description: This function is used to load the global descriptor table address to GDT register
// Paramter: -
// Return: - 
void load_gdt();

struct gdt_ptr
{
	unsigned short size;
	unsigned int base_address;
}__attribute__((packed));

struct descriptor_table_entry
{
	unsigned int lower_32_entry;
	unsigned int upper_32_entry;
	
}__attribute__((packed));

struct descriptor
{
	unsigned short int lower_baseaddress;
	unsigned char upper_baseaddress_1;
	unsigned char upper_baseaddress_2;
	unsigned short int lower_limit;
	unsigned char upper_limit;
	unsigned char granularity;
	unsigned char db;
	unsigned char l64bitmode;
	unsigned char avl;
	unsigned char p_segpresent;
	unsigned char dpl;
	unsigned char descript_type;
	unsigned char segment_type;
};

extern struct gdt_ptr gdptr;

void initialize_gdt();
struct descriptor getDescriptor(unsigned int base, unsigned int limit, unsigned char type, unsigned char granul, unsigned char avl, unsigned char dpl, unsigned char s, unsigned char db, unsigned char l, unsigned char p);
struct descriptor_table_entry descriptortotableentry(struct descriptor descript);
struct descriptor tableEntrytodescriptor(struct descriptor_table_entry entry);
unsigned short priviledgeFromSelector(unsigned short selector);
unsigned short isGlobalFromSelector(unsigned short selector);
unsigned short getIndexFromSelector(unsigned short selector);
unsigned short formSegmentSelector(unsigned short index, unsigned short globallocal, unsigned short priviledgelevel);

#endif
