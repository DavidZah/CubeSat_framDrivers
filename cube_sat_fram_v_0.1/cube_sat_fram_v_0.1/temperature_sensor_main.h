/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#ifndef _TEMPERATURE_SENSOR_MAIN_H_INCLUDED
#define _TEMPERATURE_SENSOR_MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <at30tse75x.h>
#include <at30tse75x_config.h>
#include <mcp980x.h>
#include "Config/mcp23017_config.h" //mcp980x_config.h
#include <temperature_sensor.h>
#include "driver_init.h"

extern struct temperature_sensor *TEMPERATURE_SENSOR;

/**
 * \brief Initialize Temperature Sensors
 */
void temperature_sensors_init(void);

#ifdef __cplusplus
}
#endif

#endif // _TEMPERATURE_SENSOR_MAIN_H_INCLUDED
