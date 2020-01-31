/*
 * memory.h
 *
 * Created: 31.01.2020 15:11:26
 *  Author: David
 */ 


#ifndef MEMORY_H_
#define MEMORY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>

/*
 * Multiplexor config sturct
 *
 */
struct multiplexor_settings 
{
	struct mcp23017_settings *mcp23017; 
};


/** Forward declaration of multiplexor structure. */
struct multiplexor;

/**
 * \brief Interface of abstract multiplexor
 */
struct multiplexor_interface {
	float    (*read)(const struct multiplexor *const me);
	int16_t  (*config)(const struct multiplexor *const me,struct multiplexor_settings *mux_set);
	int16_t  (*set_pin_direction)(const struct multiplexor *const me,uint8_t pin,const enum gpio_direction direction);
	int16_t (*set_pin_level)(const struct multiplexor *const me,uint8_t pin,bool pin_level);
	int16_t (*set_pin_pullup)(const struct multiplexor *const me,uint8_t pin,const enum gpio_pull_mode pull_mode);
};

/**
 * \brief Abstract multiplexor
 */
struct multiplexor {
	/** The pointer to interface used to communicate with temperature sensor */
	void *io;
	/** The interface of abstract temperature sensor */
	const struct multiplexor_interface *interface;
};

/**
 * \brief Construct abstract multiplexor
 *
 * \param[in] me The pointer to multiplexor initalize
 * \param[in] io The pointer to instance of interface to multiplexor
 * \param[in] interface The pointer to interface of multiplexor
 *
 * \return pointer to initialized multiplexor
 */
struct multiplexor * multiplexer_construct(struct multiplexor *const me, void *const io,
                                                        const struct multiplexor_interface *const interface);

/**
 * \brief Read data from the multiplexor UPRAVA
 *
 * \param[in] me The pointer to temperature sensor to read temperature from
 *
 * \return temperature
 */
float multiplexor_read(const struct multiplexor *const me);
/*
 * \brief Setup  
 *  
 * \param[in] me The pointer to multiplexor to setup
 *
 * \param[in] me The pointer to multiplexor_settings
 */
int16_t multiplexor_config(const struct multiplexor *const me,struct multiplexor_settings * temp_set);
/*
 * \brief input/output settings   
 *  
 * \param[in] me The pointer to multiplexor to setup
 *
 * \param[in] me pin to set input/output 
 *
 * \param[in] set to output/input  
 */
int16_t multiplexer_set_pin_direction (const struct multiplexor *const me,uint8_t pin,const enum gpio_direction direction);
/*
 * \brief input/output settings   
 *  
 * \param[in] me The pointer to multiplexor to setup
 *
 * \param[in] me pin to set low or high 
 *
 * \param[in] set to low or high (True=high)  
 */
int16_t multiplexer_set_pin_level (const struct multiplexor *const me,uint8_t pin,bool level);
#ifdef __cplusplus
}
#endif




#endif /* MEMORY_H_ */