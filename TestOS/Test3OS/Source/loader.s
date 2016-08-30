;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Name: loader.s
;; Description: This is the entry point of our Operating System. This will setup the stack to call the c code.
;;		Apart from that it will take care of other settings necessary for the OS
;; Reference: http://littleosbook.github.io/#introduction
;;	      http://wiki.osdev.org/Grub_Error_13
;;            http://wiki.osdev.org/Bare_Bones#Linking_the_Kernel
;; Date: 6/10/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global loader			; the entry symbol for ELF
extern newmain


MAGIC_NUMBER equ 0x1BADB002	; this number indicates that what follows is an OS code
ALIGNINFO equ 1<<0
MEMINFO equ 1<<1
ALIGNMODULES equ 0x00000001
FLAGS equ ALIGNINFO | MEMINFO | ALIGNMODULES			; multiboot flags
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)	; (magic number + checksum + flags = 0)

KERNEL_STACK_SIZE equ 16384	; This is the stack size which will be created when starting OS.

section .bss			; bss code start point
align 16				; the code is aligned 4 bytes
kernel_stack:			; starting point of the memory allocated for stack	
	resb KERNEL_STACK_SIZE

section .multiboot
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text:			; Text code start point.
align 4				; the code is aligned 4 bytes

loader:				; This will be the entry point of the Operating System as mentioned in linker script
	mov eax, 0xCAFEBABE
	mov esp, kernel_stack + KERNEL_STACK_SIZE	; Stack pointer will point to the end of the stack, as we push stack pointer is decreased and moves 
							; towards lower address
	push ebx					; This has multiboot info structure pointer
	call newmain
	;mov eax, 0xF00DCAFE

.loop:
	jmp .loop
