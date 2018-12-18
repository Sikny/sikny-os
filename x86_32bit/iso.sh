#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/siknyos.kernel isodir/boot/siknyos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "siknyos" {
	multiboot /boot/siknyos.kernel
}
EOF
grub-mkrescue -o siknyos.iso isodir
