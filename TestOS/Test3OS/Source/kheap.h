#ifndef KHEAP_H
#define KHEAP_H

unsigned int kmalloc_internal(unsigned int size, int align, unsigned int *physical);
unsigned int kmalloc(unsigned int size);
unsigned int kmalloc_aligned(unsigned int size);
unsigned int kmalloc_physical(unsigned int size, unsigned int *physical);
unsigned int kmalloc_physical_aligned(unsigned int size, unsigned int *physical);

#endif
