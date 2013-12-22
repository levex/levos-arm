#include <display.h>

#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTER 0x18
#define SERIAL_BUFFER_FULL (1 << 5)

static int _x = 0;

void serial_putc(char c)
{
	if (c == '\n')
	{
		for(; _x < 80;)
			serial_putc(' ');
		_x = 0;
		return;
	}
	/* Wait until the serial buffer is empty */
	while (*(volatile unsigned long*)(SERIAL_BASE + SERIAL_FLAG_REGISTER) 
						& (SERIAL_BUFFER_FULL));
	/* Put our character, c, into the serial buffer */
	*(volatile unsigned long*)SERIAL_BASE = c;
	_x ++;
}

struct display serial_display = {
	.putc = serial_putc,
	.flags = 3,
	.name = "Serial output display",
};

void serial_init()
{
	display_register(&serial_display);
}
