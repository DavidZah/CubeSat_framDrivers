/*
 * mcp980x.h
 *
 * Created: 07.07.2018 8:56:54
 *  Author: David
 */ 


#ifndef MCP980X_H_
#define MCP980X_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <temperature_sensor.h>

#define MCP980X_ERROR -1

#define  MCP980X_ERROR_NONE 0

#ifndef CONF_MCP980X_SENSOR_ADDRES
#define  CONF_MCP980X_SENSOR_ADDRES 0x18
#endif

#ifndef MCP980X_SETUP_REG 
#define MCP980X_SETUP_REG 0x01
#endif

#ifndef MCP980X_ALERT_TUPPER_REG
#define MCP980X_ALERT_TUPPER_REG 0x02
#endif

#ifndef MCP980X_ALERT_TLOWER_REG
#define MCP980X_ALERT_TLOWER_REG 0x03
#endif

#ifndef MCP980X_ALERT_TCRIT_REG
#define MCP980X_ALERT_TCRIT_REG 0x04
#endif

#ifndef MCP980X_TEMP_REG
#define MCP980X_TEMP_REG 0x05
#endif

#ifndef MCP980X_ID_REG
#define MCP980X_ID_REG 0x06
#endif

#ifndef MCP980X_DEVICE_ID_REG
#define MCP980X_DEVICE_ID_REG 0x07
#endif

#ifndef MCP980X_RESOLUTION_REG
#define MCP980X_RESOLUTION_REG 0x08
#endif

const enum mcp980x_hysteresis{
	mcp980xHysteresis_0C,
	mcp980xHysteresis_1_5C, 
	mcp980xHysteresis_3C,
	mcp980xHysteresis_6C,
	};
const enum mcp980x_resolution{
	mcp980x_resolution_0_5,
	mcp980x_resolution_0_25,
	mcp980x_resolution_0_125,
	mcp980x_resolution_0_0625, 
	};

const struct mcp980x_settings {
	float tupper;
	float lower;
	float critical; 
	
	uint8_t mcp980x_float_alarm; 
	uint8_t mcp980x_hysteresis;
	uint8_t mcp980x_resolution;
	   
	bool shutdown;
	bool ctr_loc;
	bool win_loc;
	bool int_crl;
	bool alert_stat;
	bool alert_sel;
	bool alert_pol;
	bool alert_mod;
	bool alert_cnt; 
	};


/**
 * \brief mcp980x temperature sensor
 */
struct mcp980x {
	/** The parent abstract temperature sensor */
	struct temperature_sensor parent;
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
struct temperature_sensor *mcp980X_construct(struct temperature_sensor *const me, void *const io,const uint8_t resolution);
/**
 * \brief Read temperature from the given sensor
 *
 * \param[in] me The pointer to temperature sensor to read temperature from
 *
 * \return temperature
 */
float mcp980x_read(const struct temperature_sensor *const me);

/**
 * \brief setup device by tempereture_settings
 *
 * \param[in] me The pointer to temperature sensor to setup
 *
 * \param[in] me The pointer to config struct 
 *
 * \return status
 */
int16_t mcp980x_config(const struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set);

/**
 * \brief setup device by set resolution
 *
 * \param[in] me The pointer to temperature sensor to setup resolution 
 *
 * \param[in] me The pointer to config 
 *
 * \return status
 */
int16_t _mcp980x_set_setup(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set);

int16_t _mcp980x_set_tupper(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set);

int16_t _mcp980x_set_lower(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set);

int16_t _mcp980x_set_critical(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set);

int16_t _mcp980x_set_resolution(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set);

#ifdef __cplusplus
}
#endif

#endif /* MCP98X_INCLUDE */
