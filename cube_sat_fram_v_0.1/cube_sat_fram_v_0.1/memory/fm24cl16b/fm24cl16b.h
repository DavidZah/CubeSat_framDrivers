/*
 * fm24cl16b.h
 *
 * Created: 31.01.2020 15:12:35
 *  Author: David
 */ 
#include <hal_i2c_m_sync.h>
#include "memory/memory.h"

#ifndef FM24CL16B_H_
#define FM24CL16B_H_

#ifndef FM24CL16B_ADDRES
#define  FM24CL16B_ADDRES 0xA0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief mcp980x temperature sensor
 */
struct fm24cl16b {
	/** The parent abstract temperature sensor */
	struct memory parent;
};

/**
 * \brief Construct mcp980x temperature sensor
 *
 * \param[in] me The pointer to temperature sensor to initialize
 * \param[in] io The pointer to instance of interface to actual sensor
 * \param[in] resolution The resolution of temperature sensor
 *
 * \return pointer to initialized sensor
 */
struct memory *fm24cl16b_construct(struct memory *const me, void *const io);
/**
 * \brief Read temperature from the given sensor
 *
 * \param[in] me The pointer to temperature sensor to read temperature from
 *
 * \return temperature
 */
int16_t fm24cl16b_read(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t block_to_read);
int16_t fm24cl16b_write(const struct memory *const me,int32_t addres,uint8_t *data,uint8_t num_to_write);

#ifdef __cplusplus
}
#endif




#endif /* FM24CL16B_H_ */