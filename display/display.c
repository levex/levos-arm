#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#include <string.h>
#include <display.h>

struct display *debugDisplay = 0;
struct display *currentDisplay = 0;


void display_register(struct display *d)
{
	if (d->flags & 1) {
		debugDisplay = d;
	}
	if (d->flags & 2) {
		currentDisplay = d;
	}
}

void putc(uint8_t level, char c)
{
	if(level == KERNEL_ERROR)
		debugDisplay->putc(c);
	currentDisplay->putc(c);
}

void printk_level_no_arg(uint8_t level, char *fmt)
{
	while(*fmt) putc(level, *fmt++);
	return;
}

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void __itoa(unsigned i,unsigned base,char* buf) {
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top=pos--;
	for (opos=0; opos<top; pos--,opos++)
		buf[opos] = tbuf[pos];
	buf[opos] = 0;
}

void printk(char *fmt, ...)
{

	char *s = 0;
	uint32_t level = 1;
	va_list ap;
	va_start(ap, fmt);
	for(size_t i = 0; i < strlen(fmt); i++)
	{
		if(fmt[i] == '%')
		{
			switch(fmt[i+1])
			{
				case 's': /* string */
				s = va_arg(ap, char*);
				printk_level_no_arg(level, s);
				i++;
				continue;
				case 'd':; /* decimal */
				int c = va_arg(ap, int);
				char str[32] = {0};
				__itoa(c, 10, str);
				printk_level_no_arg(level, str);
				i++;
				continue;
			}
		}
		putc(level, fmt[i]);
	}
	va_end(ap);
}
