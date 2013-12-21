export OBJS := start.o main.o

.PHONY: start all display
all: display kernel.img

start: kernel.img
	qemu-system-arm -m 128 -kernel kernel.img

start.o: start.s
	arm-elf-as -o start.o start.s

main.o: main.c
	arm-elf-gcc -Iinclude -Wall -Wextra -Werror -nostdlib -nostartfiles -ffreestanding -std=gnu99 -c main.c -o main.o

kernel.img: display main.o start.o
	arm-elf-ld -T link.ld -o kernel.img $(OBJS)

include ./display/makefile
