OBJS += lib/string.o
OBJS += lib/arm.o

lib: lib/string.o lib/arm.o

lib/string.o: lib/string.c
	arm-elf-gcc -Iinclude -Wall -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -c lib/string.c -o lib/string.o

lib/arm.o: lib/arm.c
	arm-elf-gcc -Iinclude -Wall -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99 -c lib/arm.c -o lib/arm.o
