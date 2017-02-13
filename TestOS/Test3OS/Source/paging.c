/*****************************************************************************************************
 * Name: paging.c
 * Description: This function will hold all the functions related to paging
 * References: http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html
 * Date: 2/12/2017
*****************************************************************************************************/
#include "paging.h"

unsigned int *frames;
unsigned int nframes;

page_directory *kernel_directory;
page_directory *current_directory;


static void set_frame(unsigned int frame_address)
{
	unsigned int frame = frame_address/0x1000;
	unsigned int idx = INDEX_FROM_BIT(frame);
	unsigned int offset = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << offset);
}

static void clear_frame(unsigned int frame_address)
{
	unsigned int frame = frame_address/0x1000;
	unsigned int idx = INDEX_FROM_BIT(frame);
	unsigned int offset = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << offset);
}

static unsigned int test_frame(unsigned int frame_address)
{
	unsigned int frame = frame_address/0x1000;
	unsigned int idx = INDEX_FROM_BIT(frame);
	unsigned int offset = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << offset));
}

static unsigned find_first_free_frame()
{
	unsigned int i, j, toTest;
	for(i = 0; i < INDEX_FROM_BIT(nframes); i++)
	{
		if(frames[i] != 0xFFFFFFFF)
		{
			for(j = 0; j < 32; j++)
			{
				toTest = 0x1 << j;
				if (!(frames[i]&toTest))
				{
					return i*4*8+j;
				}
			}
		}
	}

	return (unsigned int) -1;
}


void alloc_frame(page *pg, int is_kernel, int is_writable)
{
	unsigned int idx = 0;

	if(pg->frame != 0)
	{
		return;
	}
	else
	{
		idx = find_first_free_frame();
		if(idx == (unsigned int) -1)
		{	
			//ERROR no free frames available
		}
		set_frame(idx*0x1000);
		pg->present = 1;
		pg->rw = (is_writable)?1:0;
		pg->user = (is_kernel)?0:1;
		pg->frame = idx;
	}
}


void free_frame(page *pg)
{
	unsigned int frame;
	if(!(frame=pg->frame))
	{
		return;
	}
	else
	{
		clear_frame(frame);
		pg->frame = 0x0;
	}
}


void initialize_paging()
{
	unsigned int mem_end_page = 0x10000000;
	unsigned int i = 0;

	puts("\tframe creation\n",16);
	
	nframes = mem_end_page/0x1000;
	frames = (unsigned int *)kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	puts("\tdirectory creation\n",20);

	kernel_directory = (page_directory*)kmalloc_aligned(sizeof(page_directory));
	memset((unsigned int*)kernel_directory, 0, sizeof(page_directory));
	current_directory = kernel_directory;

	puts("\tframe allocation\n",18);


	while(i < placement_address)
	{
		alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
		i += 0x1000;
	}

	puts("\tabout to register irq\n",23);

	install_irq_handler(14, page_fault);

	puts("\tloading page directory\n",24);

	switch_pg_directory(kernel_directory);

	puts("\treturning\n",11);
	
}

void switch_pg_directory(page_directory *p_dir)
{
	/*current_directory = p_dir;
	//Call assembly function to set the CR3 and CR0
	switch_page_directory((unsigned int)&p_dir->tablesPhysical);*/
	current_directory = p_dir;
	//put_number_hex((unsigned int)sizeof(page));
    asm volatile("mov %0, %%cr3":: "r"(&p_dir->tablesPhysical));
    unsigned int cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page *get_page(unsigned int address, int make, page_directory *dir)
{
	unsigned int temp = 0;
	unsigned int table_idx = 0;	
	address /= 0x1000;
	table_idx = address /1024;	
	
	if(dir->tables[table_idx])
	{
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else if(make)
	{
		dir->tables[table_idx] = (page_table*)kmalloc_physical_aligned(sizeof(page_table), &temp);
		memset((unsigned int*)dir->tables[table_idx], 0, 0x1000);
		dir->tablesPhysical[table_idx] = temp | 0x7;
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else
	{
		return 0;
	}
	
}

void page_fault(struct cpu_stack_state state)
{
	unsigned int faulting_address = get_faulting_address();

	UNUSED(state);
	UNUSED(faulting_address);

	puts("PAGE FAULT\n", 11);
	
	
}
