/*
 * memory.c
 *
 * Created: 31.01.2020 15:11:13
 *  Author: David
 */ 



struct  multiplexor *multiplexer_construct(struct multiplexor *const me, void *const io,const struct multiplexor_interface *const interface)
{
	me->io        = io;
	me->interface = interface;

	return me;
}

/**
 * \brief Read data from the given multiplexor
 */
float multiplexor_read(const struct multiplexor *const me)
{
	return me->interface->read(me);
}
/*
 * \brief Setup sensor by setup struct 
 *  
 * \param[in] me The pointer to multiplexer to setup
 *
 * \param[in] me The pointer to set up struct
 */
int16_t multiplexer_set_settings(const struct multiplexor *const me,struct multiplexor_settings *mux_set)
{
	return me->interface->config(me,mux_set); 
}
/*
 * \brief Setup multiplexor output input 
 *  
 * \param[in] me The pointer to multiplexer to setup
 *
 * \param[in] me number of input/output pin
 * 
 * \param[in] is input or output 
 */
int16_t multiplexer_set_pin_direction(const struct multiplexor *const me,uint8_t pin,const enum gpio_direction direction)
{
	return me->interface->set_pin_direction(me,pin,direction);
}

/*
 * \brief input/output settings   
 *  
 * \param[in] me The pointer to multiplexor to setup
 *
 * \param[in] me pin to set input/output 
 *
 * \param[in] set to output/input  
 */
int16_t multiplexer_set_pin_level (const struct multiplexor *const me,uint8_t pin,bool level)
{
	return me->interface->set_pin_level(me,pin,level); 
}

int16_t multiplexor_set_pin_pullup(const struct multiplexor *const me,uint8_t pin,const enum gpio_pull_mode pull_mode)
{
	return me->interface->set_pin_pullup(me,pin,pull_mode);
	};