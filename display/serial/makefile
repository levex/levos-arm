OBJS += display/serial/serial.o

serial: display/serial/serial.o

display/serial/serial.o: display/serial/serial.c
	arm-elf-gcc -Iinclude -Wall -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -c display/serial/serial.c -o display/serial/serial.o
