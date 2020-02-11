
/*
 * memory_main.h
 *
 * Created: 11.02.2020 10:51:42
 *  Author: David
 */ 


#ifndef MEMORY_MAIN_
#define MEMORY_MAIN_

#ifdef __cplusplus
extern "C" {
#endif

#include <memory/fm24cl16b/fm24cl16b.h>
#include <memory.h>

#include "driver_init.h"

extern struct memory *MEMORY;

/**
 * \brief Initialize Temperature Sensors
 */
void memory_init(void);

#ifdef __cplusplus
}
#endif




#endif /* INCFILE1_H_ */