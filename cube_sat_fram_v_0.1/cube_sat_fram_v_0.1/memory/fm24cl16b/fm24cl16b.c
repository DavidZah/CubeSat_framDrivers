/*
* fm24cl16b.c
*
* Created: 31.01.2020 15:12:17
*  Author: David
*/

/**TO DO COMMENTS*/

#include "memory/fm24cl16b/fm24cl16b.h"
#include "memory/memory.h"

static const struct memory_interface fm24cl16b_interface = {fm24cl16b_read,fm24cl16b_write};

struct memory *fm24cl16b_construct(struct memory *const me, void *const io)
{
	struct i2c_m_sync_desc *descr;
	struct memory_interface * fm24 = (struct fm24cl16b_interface *)me;

	memory_construct(me, io, &fm24cl16b_interface);
	descr = (struct i2c_m_sync_desc *)(me->io);
	
	
	i2c_m_sync_set_slaveaddr(descr,FM24CL16B_ADDRES,I2C_M_SEVEN);

	return me;
}

int16_t fm24cl16b_read(const struct memory *const me){
	return 0; 
}

int16_t fm24cl16b_write(const struct memory *const me){
	return 0; 
}