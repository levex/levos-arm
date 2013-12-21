#include <stdint.h>
#include <stdarg.h>
#include <display.h>

struct display *debugDisplay = 0;


void display_register(struct display *d)
{
	if (d->flags & 1) {
		debugDisplay = d;
	} else {
		/* TODO */
	}
}

void putc(uint8_t level, char c)
{
	if(level == KERNEL_ERROR)
		debugDisplay->putc(c, 0, 0);
}

void printk_level_no_arg(uint8_t level, char *fmt)
{
	while(*fmt) putc(level, *fmt++);
	return;
}

void printk(char *fmt)
{
	printk_level_no_arg(1, fmt);
}
