asm_source_files := $(shell find src -name *.asm)
asm_object_files := $(patsubst src/%.asm, build/%.o, $(asm_source_files))

c_source_files := $(shell find src -name *.c)
c_object_files := $(patsubst src/%.c, build/%.o, $(c_source_files))

object_files := $(c_object_files) $(asm_object_files)

$(c_object_files): build/%.o : src/%.c
	mkdir -p $(dir $@) && \
	i686-elf-gcc -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra $(patsubst build/%.o, src/%.c, $@) -o $@

$(asm_object_files): build/%.o : src/%.asm
	mkdir -p $(dir $@) && \
	nasm -felf32 $(patsubst build/%.o, src/%.asm, $@) -o $@

.PHONY: build
build: $(object_files)
	mkdir -p isodir/boot/grub && \
	i686-elf-gcc -n -o isodir/boot/kernel.bin -T src/linker.ld -ffreestanding -O2 -nostdlib -lgcc $(object_files) && \
	cp grub.cfg isodir/boot/grub/grub.cfg && \
	grub-mkrescue -o kernel.iso isodir

clean:
	rm -rf kernel.iso isodir build