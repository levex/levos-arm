OBJS += display/display.o


display: display/display.o serial

display/display.o: display/display.c
	arm-elf-gcc -I../include -Wall -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -c display/display.c -o display/display.o

include display/serial/makefile
