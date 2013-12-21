OBJS += display/serial/serial.o

serial: display/serial/serial.o

display/serial/serial.o: display/serial/serial.c
	arm-elf-gcc -I../../include -Wall -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -c vserial.c -o display/serial/serial.o
