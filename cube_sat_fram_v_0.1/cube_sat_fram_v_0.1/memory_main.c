/*
 * memory_main.c
 *
 * Created: 11.02.2020 10:51:32
 *  Author: David
 */ 
#include "memory_main.h"

static struct fm24cl16b memory_descr;

struct memory *Memory_1;

void memory_init(void)
{
	Memory_1 = fm24cl16b_construct(&memory_descr.parent, &I2C_0);
	memory_read(Memory_1,0,0,0); 
}
