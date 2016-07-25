;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Name: io.s
; Description: This file will have all the functions related to display I/O port
; reference:  https://littleosbook.github.io/#interacting-with-the-hardware
; Date:	7/24/2016
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global outb

; Name: outb
; Description: sends a byte to an I/O port.
; stack structure when this function is called - [esp + 8] the data byte
;						 [esp + 4] the I/O port
;						 [esp    ] return address
; parameter: -
; return: - 
outb:
	mov al, [esp + 8]	; al should have the data to be sent to I/O port
	mov dx, [esp + 4]	; address of the I/O port should be present in the dx register
	out dx, al		; this will send the data in AL to I/O port indicated by the address in DX
	ret
