/*
 * memory.c
 *
 * Created: 31.01.2020 15:11:13
 *  Author: David
 */ 
#include <memory/memory.h>


struct  memory *memory_construct(struct memory *const me, void *const io,const struct memory_interface *const interface)
{
	me->io        = io;
	me->interface = interface;

	return me;
}

/**
 * \brief Read data from the given memory 
 */
int16_t memory_read(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t num_to_read)
{
	return me->interface->read(me,addres,data,num_to_read);
}

int16_t memory_write(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t num_to_write)
{
	return me->interface->write(me,addres, data, num_to_write); 
}


