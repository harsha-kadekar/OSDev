


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

