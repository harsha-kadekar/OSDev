;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Name: boot_1.asm
;; Description: This is the first stage simple bootloader for a DOS like OS
;; References: http://www.brokenthorn.com/Resources/OSDev3.html
;; Date: 6/10/2016 - 1st version
;;		 6/11/2016 - 2nd version
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

org	0x7c00						;BIOS will be loading bootloader at address ox7c00

bits 16							;When system starts in x86 it will be in real mode where address bus has 20bits but register size was 16 bits

start:
	jmp loader

msg db "Welcome to Test4OS Operating System!", 0

; OEM Parameter Block - Describes the file system

bpbOEM	db "Test4OS "

bpbBytesPerSector:	DW 512
bpbSectorsPerCluster: DB 1
bpbReservedSectors:	DW 1
bpbNumberOfFATs:	DB 2
bpbRootEntries:		DW 224
bpbTotalSectors:	DW 2880
bpbMedia:			DB 0xF0
bpbSectorsPerFAT:	DW 9
bpbSectorsPerTrack:	DW 18
bpbHeadsPerCylinder:	DW 2
bpbHiddenSectors:	DD 0
bpbTotalSectorsBig:	DD 0
bsDriveNumber:	DB 0					; 0 is for floppy disk. When running in disk like cd rom, this needs to be changed
bsUnused:	DB 0
bsExtBootSignature:	DB 0x29
bsSerialNumber:	DD 0xa0a1a2a3
bsVolumeLabel:	DB "MOS DISK   "
bsFileSystem:	DB "FAT12   "

; Printing a string
print:
	lodsb
	or al,al					; Check if 0 that is end of string has occured
	jz printdone
	mov ah, 0eh
	int 10h
	jmp print

printdone:
	ret
	

loader:

	;xor ax, ax
	;mov ds, ax
	;mov es, ax
	;mov si, msg
	;call print

	;cli
	;hlt

	.Reset:						
		mov ah, 0			; reset floppy disk function. Make the disk readers head to move to the beginning of the disk
		mov dl, 0			; drive 0 is for the floppy disk -- Remember this needs to be changed to something else basically for hard disk
		int 0x13			; call BIOS interrupt
		jc .Reset			; if carry flag set then some error has occurred, so try gain by repeating the work
	
		mov ax, 0x1000		; the read disk data will be put at address 0x1000:0
		mov es, ax			
		xor bx, bx
	
		mov ah, 0x02			; read disk sector function
		mov al, 1			; read one sector
		mov ch, 1			; this is track number I guess, so as of now it is still track 1
		mov cl, 2			; Sector number to read
		mov dh, 0			; head number
		mov dl, 0			; drive number, for floppy it is 0, when we use other, change it.
		int 0x13			; call BIOS interrupt
	
		jmp 0x1000:0x0

		load_root:
			; compute the size of root directory and store in cx
			xor cx, cx
			xor dx, dx
			mov ax, 0x0020						; there are 32 byte directory entry
			mul WORD [bpbRootEntries]			; total size of directory
			div WORD [bpbBytesPerSector]		; sectors used by directory
			xchg ax, cx

			; compute location of root directory and store in "ax"

			mov al, BYTE [bpbNumberOfFATs]
			mul WORD [bpbSectorsPerFAT]
			add ax, WORD [bpbReservedSectors]
			mov WORD [datasector], ax
			add WORD [datasector], cx

			; read root directory into memory (7c00:0200)

			mov bx, 0x0200
			call ReadSectors

			; browse root directory for binary image
	
times 510 - ($-$$) db 0     ;bootloader should fill fist sector that is 512 bytes. So except last 2 bytes other remaining bytes apart from instructions above are filled with 0.
	
dw 0xAA55					; This is the boot signature. BIOS when it reads 1st sector looks for this to confirum that it is bootable. And it should be at 511 and 512th byte of sector