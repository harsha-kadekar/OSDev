#ifndef PAGING_H
#define PAGING_H

#include "kheap.h"
#include "interrupts.h"
#include "iodisplay.h"
#include "common_functions.h"

#define UNUSED(x) (void)(x)

#define INDEX_FROM_BIT(a)	(a/(8*4))
#define OFFSET_FROM_BIT(a)	(a%(8*4))

void switch_page_directory(unsigned int );
void invalidate_page_table_entry(unsigned int);
unsigned int get_faulting_address();

typedef struct page_detailed_t
{
	unsigned char present;
	unsigned char rw;
	unsigned char user;
	unsigned char accessed;
	unsigned char dirty;
	unsigned char unused;
	unsigned int frame;
}page_detailed;

struct page_t
{
	//unsigned int value;
	unsigned int present:1;
	unsigned int rw:1;
	unsigned int user:1;
	unsigned int accessed:1;
	unsigned int dirty:1;
	unsigned int unused:7;
	unsigned int frame:20;
}__attribute__((packed));

typedef struct page_t page;

typedef struct page_table_t
{
	page pages[1024];
}page_table;

typedef struct page_directory_t
{
	page_table *tables[1024];

	unsigned int tablesPhysical[1024];

	unsigned int physicalAddress;
}page_directory;

extern unsigned int placement_address;

void alloc_frame(page *pg, int is_kernel, int is_writable);
void free_frame(page *pg);
void initialize_paging();
void switch_pg_directory(page_directory *p_dir);
page *get_page(unsigned int address, int make, page_directory *dir);
void page_fault(struct cpu_stack_state state);

#endif
