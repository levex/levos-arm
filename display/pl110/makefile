OBJS += display/pl110/pl110.o

pl110: display/pl110/pl110.o

display/pl110/pl110.o: display/pl110/pl110.c
	arm-elf-gcc -Iinclude -Wall -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -c display/pl110/pl110.c -o display/pl110/pl110.o
