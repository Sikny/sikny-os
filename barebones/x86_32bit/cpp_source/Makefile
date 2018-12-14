# export PATH="$HOME/opt/cross/bin:$PATH"

KERNEL:=kernel/
OBJPATH:=$(KERNEL)/obj/
INC=-Ikernel/include/

OBJS:=$(OBJPATH)/tty.o

CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell i686-elf-g++ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell i686-elf-g++ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -print-file-name=crtend.o)
CRTN_OBJ=crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

SOURCE=\
	$(KERNEL)/src/tty.cpp\

clean:
	rm $(OBJPATH)/*

all: boot $(OBJFILES) link

boot: boot.s
	i686-elf-as boot.s -o boot.o

$(OBJFILES):	$(SOURCE)
	i686-elf-g++ $(SOURCE) -o $(OBJFILES) -ffreestanding -O2 -Wall $(INC) -Wextra -fno-exceptions -fno-rtti

kernel:
	i686-elf-g++ -c $(KERNEL)/kernel.cpp -o $(OBJPATH)/kernel.o -ffreestanding -O2 -Wall $(INC) -Wextra -fno-exceptions -fno-rtti

link: linker.ld boot.o $(OBJPATH)/kernel.o
	i686-elf-gcc -T linker.ld -o siknyos.bin -ffreestanding -O2 -nostdlib boot.o $(OBJFILES) -lgcc

install:
	mkdir -p isodir/boot/grub
	cp siknyos.bin isodir/boot/siknyos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o siknyos.iso isodir

qemu:
	qemu-system-i386 -cdrom siknyos.iso
