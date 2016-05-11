global read_CR0
global write_CR0
global read_CR4
global write_CR4
global read_CR3
global write_CR4

; Name: read_CR0
; Description: Read the contents of Control Register CR0
;	      [eax] - Contents of CR0
read_CR0:
	mov eax, cr0
	ret

; Name: write_CR0
; Description: Write the contents of Control Register CR0. 
;	       Usually to manipulate Paging settings

write_CR0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
	ret

; Name: read_CR3
; Description: Read the contents of Control Register CR3
;	      [eax] - Contents of CR3
read_CR3:
	mov eax, cr3
	ret

; Name: write_CR3
; Description: Write the contents of Control Register CR3. 
;	       Usually to manipulate Paging settings

write_CR3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	ret

; Name: read_CR0
; Description: Read the contents of Control Register CR0
;	      [eax] - Contents of CR0
read_CR0:
	mov eax, cr0
	ret

; Name: write_CR4
; Description: Write the contents of Control Register CR4. 
;	       Usually to manipulate Paging settings

write_CR4:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr4, eax
	pop ebp
	ret



ENABLE_PAGING:
;EAX has the physical address of the Page Directory - First entry to the Hierarchy Paging
mov cr3, eax

;Once CR3 is set, now enable paging by setting necessary bits in CR0 and CR4
mov ebx, cr4
or ebx, 0x00000010	;SETTING PSE bit in CR4 register
mov cr4, ebx

mov ebx, cr0
or ebx, 0x800000000	;SETTING PG bit in CR0 register. Remember if you set PG first without setting PSE, then triple fault will occur.
mov cr0, ebx

