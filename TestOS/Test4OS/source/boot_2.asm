;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Name: boot_2.asm
;; Description: This is the 2nd stage of the bootloader
;; References: http://www.brokenthorn.com/Resources/OSDev6.html
;; Date: 1st stage - 6/11/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

org 0x0			;going to load the program at address 0. Remember it may not be actual address 0

bits 16

jmp main

print:
		lodsb
		or al,al
		jz printdone
		mov ah, 0eh
		int 10h
		jmp print

printdone:
		ret

main:
	cli
	push cs
	pop ds

	mov si, msg
	call print

	cli
	hlt

msg db "preparing 2nd stage loader....", 13, 10, 0