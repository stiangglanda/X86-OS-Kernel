# 32-bit Operating System Kernel

## Prerequisites

 - A text editor such as [VS Code](https://code.visualstudio.com/).
 - [Docker](https://www.docker.com/) for the build-environment.
 - emulation software such as [Qemu](https://www.qemu.org/).

## Setup

Build an image for our build-environment:
 - `docker build env -t os-buildenv`

## Build

Enter build environment:
 - Linux or MacOS: `docker run --rm -it -v "$(pwd)":/root/env os-buildenv`
 - Windows (CMD): `docker run --rm -it -v "%cd%":/root/env os-buildenv`
 - Windows (PowerShell): `docker run --rm -it -v "${pwd}:/root/env" os-buildenv`

To leave the build environment, enter `exit`.

### Using Make

`make build`

### Manual
- `nasm -felf32 src/boot.asm -o boot.o`
- `i686-elf-gcc -c src/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra`
- `i686-elf-gcc -T src/linker.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc`
- `mkdir -p isodir/boot/grub`
- `cp grub.cfg isodir/boot/grub/grub.cfg`
- `cp os.bin isodir/boot/os.bin`
- `grub-mkrescue -o os.iso isodir`

## Emulate

 - `qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso`

## Cleanup

Remove the build-evironment image:
 - `docker rmi os-buildenv -f`


https://github.com/user-attachments/assets/b4b1acdb-35e9-4001-a2e1-19d0331125bc

