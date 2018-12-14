all: boot kernel link

boot: boot.s
	i686-elf-as boot.s -o boot.o

kernel:	kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

link: linker.ld boot.o kernel.o
	i686-elf-gcc -T linker.ld -o siknyos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

install:
	mkdir -p isodir/boot/grub
	cp siknyos.bin isodir/boot/siknyos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o siknyos.iso isodir

qemu:
	qemu-system-i386 -cdrom siknyos.iso
