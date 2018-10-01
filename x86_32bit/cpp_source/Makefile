all: boot kernel link

boot: boot.s
	i686-elf-as boot.s -o boot.o

kernel:	kernel.cpp
	i686-elf-g++ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

link: linker.ld boot.o kernel.o
	i686-elf-gcc -T linker.ld -o siknyos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

install:
	mkdir -p isodir/boot/grub
	cp siknyos.bin isodir/boot/siknyos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o siknyos.iso isodir

qemu:
	qemu-system-i386 -cdrom siknyos.iso
