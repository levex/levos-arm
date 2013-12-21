#include <display.h>

#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTER 0x18
#define SERIAL_BUFFER_FULL (1 << 5)


void serial_putc(char c, uint32_t x, uint32_t y)
{
    /* Wait until the serial buffer is empty */
    while (*(volatile unsigned long*)(SERIAL_BASE + SERIAL_FLAG_REGISTER) 
                                       & (SERIAL_BUFFER_FULL));
    /* Put our character, c, into the serial buffer */
    *(volatile unsigned long*)SERIAL_BASE = c;

    /* TODO */
}

struct display serial_display = {
	.putc = serial_putc,
	.flags = 1,
	.name = "Serial output display",
};

void serial_init()
{
	display_register(&serial_display);
}
