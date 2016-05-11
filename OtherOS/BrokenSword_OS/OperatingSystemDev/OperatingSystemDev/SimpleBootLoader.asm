;*************************************************************************
;					SimpleBootLoader.asm
;							- A simple Boot Loader
;					Operating System Development Tutorial
;*************************************************************************

;org		0x7c00		;We are loaded by BIOS at address 0x7c00

bits	16			;We are still in 16 bit real Mode
org 0

Start:
		jmp main						;jmp loader			; jump over OEM block

;_______________________________________________________________________________
;				OEM Parameter block
;_________________________________________________________________________________

bpbOEM						db "My OS HK"					;This must be exactly 8 bytes why???

bpbBytesPerSector:			dw 512							;How many bytes are present in a sector
bpbSectorsPerCluster:		db 1							;Each cluster consists of how many sectors.
bpbReservedSectors:			dw 1							;In the drive how many sectors are reserved including the boot sector
bpbNumberOfFATs:			db 2							;How many FAT tables are stored
bpbRootEntries:				dw 224							;Basically how many maximum directories can be formed in a root directory
bpbTotalSectors:			dw 2880							;Total number of sectors present in the floppy drive
bpbMedia:					db 0xF0							;this is a bit valued - bit 0:0 if drive is single sided else 1 if double sided, Bit 1:0 if FAT is stored in 9 sectors, 1 if stored in 8 sectors , Bit 2:0 if it has 80 sectors, else 1 for 40 sectors, Bit3: 0 for fixed drive(hard drive) else 1 for removable disk, Bit 4 to 7 always 1 
bpbSectorsPerFAT:			dw 9							; Each FAT table is stored in 9 sectors.
bpbSectorsPerTrack:			dw 18							; How many sectors present in a track
bpbHeadsPerCylinder:		dw 2							;For a cylinder how many heads are present
bpbHiddenSectors:			dd 0							;How many sectors are treated as hidden
bpbTotalSectorsBig:			dd 0							;
bsDriveNumber:				db 0							;What is the current drives number, for floppy its usually 0
bsUnused:					db 0							;
bsExtBootSignature:			db 0x29							;This is the BIOS Parameter Block type and version. 0x28 and 0x29 represents the MS/PC-DOS version 4.0
bsSerialNumber				dd 0xa0a1a2a3					;This is a unique numbers assigned for each drive. In every drive it will be different. Each time when we format the disk that time it will be automatically added, as currently we are overwritting that we are just entering random number
bsVolumeLabel:				db "MOS FLOPPY "				;This just indicates what is there on the disk
bsFileSystem:				db "FAT12   "					;Type of filesystem used by the drive

msg		db		"Welcome to My Operating System!", 0			;String to pint by boot loader

;______________________________________________________________________________________________
;				Prints a string
;				DS=>SI 0 terminated string
;_______________________________________________________________________________________________

Print:
				lodsb											;load next byte from string from SI to AL
				or		al, al									;Does al = 0?
				jz		PrintDone								;If al = 0 then done printing, found null terminator.
				mov		ah, 0eh									;If al != 0 then print the character
				int		10h								
				jmp		Print									;Repeat untill we find the null terminator
PrintDone:	
				ret												;completed printing, so return



;_____________________________________________________________________________________________________
;				This will read the sectors
;				cx=>Number of Sectors to read
;				ax=>Starting sector
;				ES:BX=>Buffer to read to
;______________________________________________________________________________________________________

ReadSectors:
	.MAIN
		mov di, 0x0005										;5 reatries incase an error occurs

	.SECTORLOOP
		push ax
		push bx
		push cx

		call LBACHS										   ;Converting the starting sector LBA to CHS. 
		mov ah, 0x02									   ;BIOS read sector
		mov al, 0x01									   ;Read one sector.
		mov ch, BYTE [absoluteTrack]
		mov cl, BYTE [absoluteSector]
		mov dh, BYTE [absoluteHead]
		mov dl, BYTE [bsDriveNumber]
		int 0x13										; invoke BIOS
		jnc .SUCCESS
		xor ax, ax
		int 0x13
		dec di
		pop cx
		pop bx
		pop ax
		jnz .SECTORLOOP
		int 0x18
	.SUCCESS
		mov si, msgProgress
		call Print
		pop cx
		pop bx
		pop ax
		add bx, WORD [bpbBytesPerSector]				;Queue next buffer i.e. now one sector ie equal to 512 bytes is read now keep ready next 512 bytes free to read next sector
		inc ax											;Next Sector number ie LBA to be read.
		loop .MAIN										;Read the sector. ;CX contains the number of sectors to read and loop instruction will use it.
        ret

;_________________________________________________________________
; absolute sector 	= 	(LBA % sectors per track) + 1
; absolute head   	= 	(LBA / sectors per track) % number of heads
; absolute track 	= 	 LBA / (sectors per track * number of heads)
;_________________________________________________________________
LABCHS:
	xor dx, dx
	div WORD [bpbSectorsPerTrack]					;dx = 0, ax = Starting sector; (LBA % sectors per track)
	inc dl											; +1
	mov BYTE [absoluteSector], dl
	xor dx, dx
	div WORD [bpbHeadsPerCylinder]					;at this point ax has LBA/sectors per tack value, so directly mod by number of heads -> (LBA / sectors per track) % number of heads
	mov BYTE [absoluteHead], dl
	mov BYTE [absoluteTrack], al					;Ok in previous step we have finished all the operations i.e. absolute head and absolute track are same operation but one is interested in remider and other in quotient :-)
	ret

;_________________________________________________________________________
;LBA	=	(cluster - 2 ) * sectors per cluster
;ax = Cluster Number
;_________________________________________________________________________
ClusterLBA:
	sub ax, 0x0002
	xor cx, cx
	mov cl, BYTE [bpbSectorsPerCluster]
	mul cx
	add ax, WORD [datasector]			;From data Sector + LBA to give exact location
	ret


	;------------------------------------------------------------------------------------------
	;Order of sectors
	;------------------------------------------------------------------------------------------

;_____________________________________________________________________________________________________________________________________________________________________________________________
;Boot Sector	:::	Extra Reserved Sectors	:::	File Allocation Table 1	:::	File Allocation Table 2	:::	Root Directory (FAT12/FAT16 Only)	:::	Data Region containng files and directories.
;______________________________________________________________________________________________________________________________________________________________________________________________



;________________________________________________________________________________________________
;				Bootloader Entry Point
;_________________________________________________________________________________________________


main:

	;-------------------------------------------------------------------
	;Code is loaded at the address 0000:7C00, adjust segment registers
	;--------------------------------------------------------------------

	cli																;disable all the interrupts
	mov ax, 0x7c00																										
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;-------------------------------------------------------------------
	;Creating the Stack
	;--------------------------------------------------------------------
	mov ax, 0x0000													;Set the Stack
	mov ss, ax														;Setting the Stack Segment
	mov sp, 0xFFFF													;Setting the Stack Pointer
	sti																;Restore interrups

	;----------------------------------------------------------------------
	;Show loading message
	;-----------------------------------------------------------------------

	mov si, msgLoading
	call Print


	;----------------------------------------------------------------------
	;Loading the root directory table
	;----------------------------------------------------------------------
LOAD_ROOT:

	;----------------------------------------------------------------------
	;Compute the size of the root directory
	;----------------------------------------------------------------------
	xor cx, cx
	xor dx, dx
	mov ax, 0x0020													;Each entry in the directory is 32 bytes
	mul WORD [bpbRootEnteries]										;total number of entries possible in the root directory x size of the each entry  = total number of bytes for the root directory
	div WORD [bpbBytesPerSector]									;Divide total number of bytes for root directory by number of bytes per sector = Total sectors needed for root directory.
	xchg ax, cx

	;---------------------------------------------------------------------------------
	;Compute the location of root directory ie starting sector of the root directory
	;---------------------------------------------------------------------------------
	mov al, BYTE [bpbNumberOfFATs]									;Each FAT table needs bpbNumberOfFATs sectors to store
	mul WORD [bpbSectorsPerFAT]										;Multiplty number of sectors needed by each FAT table with number of FAT tables present
	add ax, WORD [bpbReservedSectors]								;Add that with the number reserved bytes [this includes boot sector]. This sum indicates the starting sector of the root directory.
	mov WORD [datasector], ax										; BOOTSECTOR::RESERVED::FAT1::FAT2::ROOTDIRECTORY::DATA
	add WORD [datasector], cx										;Finding from which sectors data is present. Its usually after root directory

	;----------------------------------------------------------------------------------
	;read root directory into memory at location 7C00:0200
	;----------------------------------------------------------------------------------
	mov bx, 0x0200			
	call ReadSectors

	;---------------------------------------------------------------------------------
	; Find the file having Step2 of the boot loader.
	;---------------------------------------------------------------------------------
	mov cx, WORD [bpbRootEntries]					;Number of directories  the Root directory can hold.
	mov di, 0x0200									;Each file entry is 32 bytes

	.LOOP
		push cx
		mov cx, 0x000B								;Each file has 11 bytes name 
		mov si, ImageName
		push di

		rep cmpsb
		pop di
		je LOAD_FAT
		pop cx
		add di, 0x0020							    ;Try for the next directory entry
		loop .LOOP
		jmp FAILURE

  LOAD_FLAT:
	
	;-------------------------------------------------------------------------------
	;Find the cluster where the 2nd Stage boot loader is stored.
	;-------------------------------------------------------------------------------
	mov si, msgCRLF
	call Print
	mov dx, WORD [di + 0x001A]						;Once we have find the file, 26th byte of that files entry will give you the starting cluster number of FAT.
	mov WORD [cluster], dx

	;-------------------------------------------------------------------------------
	;How many sectors does the FAT is taking. Usually Number of FAT * Number of Sectors for each FAT
	;-------------------------------------------------------------------------------
	xor ax, ax
	mov al, BYTE [bpbNumberOfFATs]
	mul WORD [bpbSectorsPerFAT]
	mov cx, ax

	mov ax, WORD [bpbReservedSectors]					;Remember this includes the initial boot sector so it will be always 1 + something.


	;---------------------------------------------------------------
	; read FAT into memory (7C00:0200)
	;----------------------------------------------------------------
	mov bx, 0x0200
	call ReadSectors									;CX = Number of Sectors used for FAT, AX= After the reserved Sectors, So basically we are reading FAT.
	

	mov si, msgCRLF
	call Print
	mov ax, 0x0050										;Load the File at location 0050:0000
	mov es, ax
	mov bx, 0x0000
	push bx


 LOAD_IMAGE:
	mov ax,	WORD [cluster]
	pop bx
	call ClusterLBA
	xor cx, cx
	mov cl, BYTE [bpbSectorsPerCluster]
	call ReadSectors
	push bx

	mov ax, WORD [cluster]
	mov cx, ax
	mov dx, ax
	shr dx, 0x0001
	add cx, dx
	mov bx, 0x0200
	add bx, cx
	mov dx, WORD [bx]
	test ax, 0x0001
	jnz .ODD_CLUSTER

	.EVEN_CLUSTER
		and dx, 0000111111111111b
		jmp .DONE

	.ODD_CLUSTER
		shr dx, 0x0004

	.DONE
		mov WORD [cluster], dx
		cmp dx, 0x0FF0
		jb LOAD_IMAGE


	DONE:
		mov si, msgCRLF
		call Print
		push WORD 0x0050
		push WORD 0x0000
		retf

    FAILURE:
		mov si, msgFalure
		call Print
		mov ah, 0x00
		int 0x16
		int 0x19


	absoluteSector db 0x00
	absoluteHead db 0x00
	absoluteTrack db 0x00

	datasector dw 0x0000
	cluster dw 0x0000
	ImageName db "KRNLDR  SYS"
	msgLoading db 0x0D, 0x0A, "Loading Boot Image", 0x0D, 0x0A, 0x00
	msgCRLG db 0x0D, 0x0A, 0x00
	msgProgress db ".", 0x00
	msgFailure db 0x0d, 0x0a, "ERROR : Press any key to reboot", 0x0a, 0x00

	times 510 - ($-$$)	db 0		;We have to be 512 bytes. Clear the rest of the bytes with 0

	dw 0xAA55						;Boot Signature




