#include <stdint.h>
#include <display.h>
#include <pl110.h>


#define __LEVOS_VERSION__ 221213

int main (void)
{
	/* Start up serial display at least */
	serial_init();
	/* Setup pl110 video */
	pl110_init();
	pl110_clear();
	printk("Serial output... OK.\n");
	printk("LevOS-ARM %d loaded.\n", __LEVOS_VERSION__);
	printk("pl110 video... OK\n");
	printk("kernel panic: reached end of main()!\n");
	return 0;
}
