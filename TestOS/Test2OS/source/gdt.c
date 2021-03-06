#include "gdt.h"

/*
This file creates the global descriptor table and then loads the GDTR register.

*/

/*1. Null 2. Code segment - read and execute 3. Data segement - read and write*/
struct gdt_entry global_gdt[3]; 
struct gdt gdt_ptr;

void init_gdt_descriptor_table()
{
   gdt_ptr.limit = (sizeof(struct gdt_entry) * 3) - 1;
   gdt_ptr.base  = (unsigned int)&global_gdt;

   //Implementing Flat Model of Segmentation
   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   //gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   //gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdt_flush();
	
}


void gdt_set_gate(int index, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran)
{
   global_gdt[index].base_address    = (base & 0xFFFF);
   global_gdt[index].first_base = (base >> 16) & 0xFF;
   global_gdt[index].second_base   = (base >> 24) & 0xFF;

   global_gdt[index].segment_limit   = (limit & 0xFFFF);
   global_gdt[index].avl_granularity = (limit >> 16) & 0x0F;

   global_gdt[index].avl_granularity |= gran & 0xF0;
   global_gdt[index].type_dpl_present      = access;
} 
