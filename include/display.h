#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <stdint.h>

#define KERNEL_INFO 0
#define KERNEL_ERROR 1

struct display {
	void (*putc)(char c);
	uint8_t flags;
	char *name;
};

extern void display_register(struct display *d);

extern void printk(char *str);


extern void serial_init();


#endif
