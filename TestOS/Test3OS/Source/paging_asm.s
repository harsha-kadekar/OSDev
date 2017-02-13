;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Name: paging.s
; Description: This file has all the assembly functions which help in enabling or switching of pages
; References: https://littleosbook.github.io/#paging
;	      https://github.com/littleosbook/aenix/blob/master/src/kernel/paging_asm.s
; Date: 2/12/2017
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global switch_page_directory
global invalidate_page_table_entry
global get_faulting_address

switch_page_directory:
	mov eax, [esp+4]
	mov cr3, eax

	mov ebx, cr4
	or ebx, 0x00000010
	mov cr4, ebx
	
	mov ebx, cr0
	or ebx, 0x80000000
	mov cr0, ebx
	
	ret

invalidate_page_table_entry:
	mov eax, [esp + 4]
	invlpg[eax]
	ret

get_faulting_address:
	mov eax, cr2
	ret
