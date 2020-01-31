/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */

#include "temperature_sensor_main.h"

static struct mcp980x TEMPERATURE_SENSOR_descr;

struct temperature_sensor *TEMPERATURE_SENSOR;

/**
 * \brief Initialize Temperature Sensors
 */
void temperature_sensors_init(void)
{
	i2c_m_sync_enable(&I2C_0);
	TEMPERATURE_SENSOR = mcp980X_construct(&TEMPERATURE_SENSOR_descr.parent, &I2C_0, 0);
}
