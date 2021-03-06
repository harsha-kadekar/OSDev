;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Name: interrupts_asm.s
; Description: This file has assembly functions related to interrupts handling like loading interrupting descriptor table, interrupt handlers, etc
; References: https://littleosbook.github.io/#interrupts-and-input
; Date: 8/6/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	cli
	push dword 0
	push dword %1
	jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1:
interrupt_handler_%1:
	cli
	push dword %1
	jmp common_interrupt_handler
%endmacro

%macro irq_code_handler 2
global interrupt_request_%1
interrupt_request_%1:
	cli
	push DWORD 0
	push DWORD %2
	jmp common_interrupt_request_handler
%endmacro

global load_idt

extern idtptr
extern interrupt_handler
extern interrupt_request_handler

section .text:

; Name: load_idt
; Description: This function will load the interrtupt descriptor table to the IDTR register
;		stack when function called ->   [esp ]  - return address
; Parameters: -
; Return: -
load_idt:
	lidt [idtptr]
	ret

common_interrupt_handler:
	push esp
	add DWORD [esp], 8
	push eax
	push ebx
	push ecx
	push edx
	push ebp
	push esi
	push edi

	call interrupt_handler
	
	pop edi
	pop esi
	pop ebp
	pop edx
	pop ecx
	pop ebx
	pop eax
	pop esp

	sti

	iret

common_interrupt_request_handler:
	push esp
	add DWORD [esp], 8
	push eax
	push ebx
	push ecx
	push edx
	push ebp
	push esi
	push edi

	call interrupt_request_handler

	pop edi
	pop esi
	pop ebp
	pop edx
	pop ecx
	pop ebx
	pop eax
	pop esp
	
	sti

	iret

no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
no_error_code_interrupt_handler 7
error_code_interrupt_handler 8
no_error_code_interrupt_handler 9
error_code_interrupt_handler 10
error_code_interrupt_handler 11
error_code_interrupt_handler 12
error_code_interrupt_handler 13
error_code_interrupt_handler 14
no_error_code_interrupt_handler 15
no_error_code_interrupt_handler 16
error_code_interrupt_handler 17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
no_error_code_interrupt_handler 21
no_error_code_interrupt_handler 22
no_error_code_interrupt_handler 23
no_error_code_interrupt_handler 24
no_error_code_interrupt_handler 25
no_error_code_interrupt_handler 26
no_error_code_interrupt_handler 27
no_error_code_interrupt_handler 28
no_error_code_interrupt_handler 29
no_error_code_interrupt_handler 30
no_error_code_interrupt_handler 31

irq_code_handler 0, 32
irq_code_handler 1, 33
irq_code_handler 2, 34
irq_code_handler 3, 35
irq_code_handler 4, 36
irq_code_handler 5, 37
irq_code_handler 6, 38
irq_code_handler 7, 39
irq_code_handler 8, 40
irq_code_handler 9, 41
irq_code_handler 10, 42
irq_code_handler 11, 43
irq_code_handler 12, 44
irq_code_handler 13, 45
irq_code_handler 14, 46
irq_code_handler 15, 47


	
