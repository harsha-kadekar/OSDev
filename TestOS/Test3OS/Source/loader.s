;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Name: loader.S
; Description: This is the starting point of the Operating System. GRUB2 will pass control to this code
; Date: 5/25/2016
; Reference: https://littleosbook.github.io/#first-steps
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global loader				; the entry symbol for ELF

MAGIC_NUMBER	equ 0x1BADB002		; define the magic number constant
FLAGS		equ 0x0			; multiboot flags
CHECKSUM	equ -MAGIC_NUMBER	; magic_number + flags + checksum == 0

section .text:				; This is the code/text section
align 4					; code must be 4 byte aligned
	dd MAGIC_NUMBER			; write the magic number
	dd FLAGS			; write the flags
	dd CHECKSUM			; write the checksum

loader:					; This is the entry point of the OS
	mov eax, 0xCAFEBABE		
.loop:
	jmp .loop	
