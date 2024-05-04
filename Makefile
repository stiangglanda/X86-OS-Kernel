# Compiler
CC = i686-elf-gcc
ASM = nasm

# Compiler flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASMFLAGS = -f elf32

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES := $(wildcard $(SRC_DIR)/*.asm)

# Object files
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
ASM_OBJECTS := $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))

# Target executable
TARGET = my_os

.PHONY: all clean

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(TARGET): $(C_OBJECTS) $(ASM_OBJECTS)
	$(CC) -T linker.ld -o $(BUILD_DIR)/$(TARGET).bin -ffreestanding -O2 -nostdlib $(C_OBJECTS) $(ASM_OBJECTS) -lgcc && \
	mkdir -p isodir/boot/grub && \
	cp myos.bin isodir/boot/myos.bin && \
	cp grub.cfg isodir/boot/grub/grub.cfg && \
	grub-mkrescue -o myos.iso isodir

clean:
	rm -rf $(BUILD_DIR)
