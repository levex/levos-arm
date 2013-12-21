#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <stdint.h>

#define KERNEL_INFO 0
#define KERNEL_ERROR 1

struct display {
	void (*putc)(char c, uint32_t x, uint32_t y);
	uint8_t flags;
	char *name;
};

extern void display_register(struct display *d);

extern void printk(char *str);


extern void serial_init();


#endif
