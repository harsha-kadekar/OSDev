global gdt_flush

extern gdt_ptr

gdt_flush:
	lgdt [gdt_ptr]	;Loading the Global Descriptor Table address information
	mov ax, 0x10	;Loading the Code Segment. Here 0x10 is a logical address or far pointer. We are using flat model, so all the segment registers are loaded with same segment descriptors. 
	mov ds, ax	;Loading Data Segment register
	mov es, ax	;Loading Extra Segment register
	mov fs, ax	;Loading F Segment register
	mov gs, ax	;Loading g Segment register
	mov ss, ax	;Loading stack Segment register.
	jmp 0x08:flush2
flush2:
	ret
