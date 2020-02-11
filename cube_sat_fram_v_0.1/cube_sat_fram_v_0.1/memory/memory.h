/*
 * memory.h
 *
 * Created: 31.01.2020 15:11:26
 *  Author: David
 */ 

/**TO DO COOMENTS*/

#ifndef MEMORY_H_
#define MEMORY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>



/** Forward declaration of memory structure. */
struct memory;

/**
 * \brief Interface of abstract memory
 */
struct memory_interface {
	int16_t    (*read)(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t num_to_write);
	int16_t  (*write)(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t num_to_write);
};

/**
 * \brief Abstract memory
 */
struct memory {
	/** The pointer to interface used to communicate with memory */
	void *io;
	/** The interface of abstract memory */
	const struct memory_interface *interface;
};

/**
 * \brief Construct abstract multiplexor
 *
 * \param[in] me The pointer to memory initalize
 * \param[in] io The pointer to instance of interface to multiplexor
 * \param[in] interface The pointer to interface of multiplexor
 *
 * \return pointer to initialized multiplexor
 */
struct memory * memory_construct(struct memory *const me, void *const io,
                                                        const struct memory_interface *const interface);

/**
 * \brief Read data from the multiplexor UPRAVA
 *
 * \param[in] me The pointer to temperature sensor to read temperature from
 *
 * \return temperature
 */

/**TO DO COOMENTS*/
int16_t memory_read(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t num_to_read);

int16_t memory_write(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t num_to_write); 

#ifdef __cplusplus
}
#endif




#endif /* MEMORY_H_ */