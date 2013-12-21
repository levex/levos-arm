#ifndef __PL110_H_
#define __PL110_H_

#define PL110_CR_EN		0x001
#define PL110_CR_PWR		0x800
#define PL110_IOBASE		0xc0000000
#define PL110_PALBASE		(PL110_IOBASE + 0x200)

struct pl110_mmio
{
	uint32_t		volatile tim0;		//0
	uint32_t		volatile tim1;		//4
	uint32_t		volatile tim2;		//8
	uint32_t		volatile d;		//c
	uint32_t		volatile upbase;	//10
	uint32_t		volatile f;		//14
	uint32_t		volatile g;		//18
	uint32_t		volatile control;	//1c
};

extern void pl110_init();

extern void pl110_clear();

#endif
