OBJECTS = loader.o kmain.o io.o io_asm.o string_functions.o gdt.o gdt_asm.o idt.o idt_asm.o timer.o keyboard.o paging_asm.o paging.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -nostartfiles -fno-builtin -fno-stack-protector -nodefaultlibs -Wall -Wextra -Werror -fomit-frame-pointer -Wno-unused-function -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf32

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf 	*.o kernel.elf  os.iso
