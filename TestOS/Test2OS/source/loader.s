global start

MAGIC_NUMBER		equ 0x1BADB002
ALIGN_MODULES		equ 1<<0
MEMORY_INFO		equ 1<<1
FLAGS			equ ALIGN_MODULES | MEMORY_INFO
KERNEL_STACK_SIZE	equ 0x1000
CHECKSUM		equ -(MAGIC_NUMBER + FLAGS)

extern main
extern kmain		

section .text
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM


start:
	mov eax, 0xCAFEBABE
	mov esp, kernel_stack + KERNEL_STACK_SIZE
	push ebx
	;call main
	call kmain
	;int 0x00
	;int 0x01
	;push 4
	;int 0x20
	pop ebx
	int 0x21

.loop:
	jmp .loop

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE
end_kernel:
