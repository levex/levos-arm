#include <stdint.h>
#include <display.h>
#include <pl110.h>


int main (void)
{
	/* Start up serial display at least */
	serial_init();
	printk("LarmOS 0.01 loaded\n");
	/* Setup pl110 video */
	pl110_init();
	pl110_clear();
	printk("pl110 video initialized! :-)\n");
	printk("kernel panic: reached end of main()!\n");
	return 0;
}
