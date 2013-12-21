#include <stdint.h>
#include <display.h>
 
int main (void)
{
    /* Start up serial display at least */
    serial_init();
    printk("LarmOS 0.01 loaded");
    return 0;
}
