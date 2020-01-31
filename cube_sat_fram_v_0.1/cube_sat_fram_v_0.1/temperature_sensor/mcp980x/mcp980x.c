/*
 * mcp980x.c
 *
 * Created: 07.07.2018 8:56:36
 *  Author: David
 */ 

#include <mcp980x.h>
#include <hal_i2c_m_sync.h>
#include <temperature_sensor.h>
#include "mcp23017_config.h"//<mcp980x_config.h>

#define MCP980X_TEMP_REG 0x05


static const struct temperature_sensor_interface mcp980x_interface = {mcp980x_read, mcp980x_config};

struct temperature_sensor *mcp980X_construct(struct temperature_sensor *const me, void *const io, const uint8_t resolution)
{
	struct i2c_m_sync_desc *descr;
	struct mcp980x *     mcp98 = (struct mcp980x *)me;

	temperature_sensor_construct(me, io, &mcp980x_interface);
	descr            = (struct i2c_m_sync_desc *)(me->io);
	
	i2c_m_sync_set_slaveaddr(descr, CONF_MCP980X_SENSOR_ADDRES, I2C_M_SEVEN);

	return me;
}

/**
 * \brief Read temperature from the given sensor
 */
float mcp980x_read(const struct temperature_sensor *const me)
{
	uint8_t buffer[2] = {0x00}; 
	buffer[0]=MCP980X_TEMP_REG;
	struct i2c_m_sync_desc *descr = (struct i2c_m_sync_desc *)(me->io);
	
	i2c_m_sync_set_slaveaddr(descr,CONF_MCP980X_SENSOR_ADDRES, I2C_M_SEVEN);
	
	io_write(&descr->io, buffer, 1);
	io_read(&descr->io, buffer, 2);
	
	int temp = ((buffer[0] & 0x1F) * 256 + buffer[1]);
	if(temp > 4095)
	{
		temp -= 8192;
	}
	float cTemp = temp * 0.0625;
	
	return cTemp; 
}

/**
 *  \brief setup sensor by tempereture sensor settings !!!DONT WORK  !!!! RETURN BAD VALUES !!!!!!
 */
int16_t mcp980x_config(const struct temperature_sensor *const me, struct tempereture_sensor_settings *temp_set)
{ 
	if(_mcp980x_set_setup(me,temp_set)==MCP980X_ERROR){
		return MCP980X_ERROR;
	}
	if(_mcp980x_set_tupper(me,temp_set)==MCP980X_ERROR){
		return MCP980X_ERROR;
	}
	
	if(_mcp980x_set_lower(me,temp_set)==MCP980X_ERROR) {
		return MCP980X_ERROR; 
	}
	if(_mcp980x_set_critical(me,temp_set)==MCP980X_ERROR){
		return MCP980X_ERROR; 
	} 
	if(_mcp980x_set_resolution(me,temp_set)==MCP980X_ERROR){
		return MCP980X_ERROR; 
	} 	
return MCP980X_ERROR_NONE; 
}

int16_t _mcp980x_set_setup(struct temperature_sensor *const me, struct tempereture_sensor_settings *temp_set)
{
	struct i2c_m_sync_desc *descr = (struct i2c_m_sync_desc *)(me->io);
	
	i2c_m_sync_set_slaveaddr(&descr->io, 0x18, I2C_M_SEVEN); 
	
	uint8_t buffer_setup[3];
	uint8_t buffer_read[2];
	
	memset(buffer_read, 0, sizeof(buffer_read));
	 
	buffer_setup[0]=MCP980X_SETUP_REG; 
	
	buffer_setup[1] = temp_set->mcp980x->mcp980x_hysteresis << 1; 
	
	if (temp_set->mcp980x->shutdown)
	{
		buffer_setup[1] +=1;
	}
	if (temp_set->mcp980x->ctr_loc)
	{
		buffer_setup[2]|=0b10000000; 
	}
	if (temp_set->mcp980x->win_loc)
	{
		buffer_setup[2]|=0b01000000; 		
	}
	if (temp_set->mcp980x->int_crl)
	{
		buffer_setup[2]|=0b00100000; 	
	}
	if (temp_set->mcp980x->alert_stat)
	{
		buffer_setup[2]|=0b00010000; 	
	}
	if (temp_set->mcp980x->alert_cnt)
	{
		buffer_setup[2]|=0b00001000; 	
	}
	if (temp_set->mcp980x->alert_sel)
	{
		buffer_setup[2]|=0b00000100; 	
	}
	if (temp_set->mcp980x->alert_pol)
	{
		buffer_setup[2]|=0b00000010; 	
	}
	if (temp_set->mcp980x->alert_mod)
	{
		buffer_setup[2]|=0b00000001; 	
	}
	
	io_write(&descr->io, buffer_setup, 3);
	delay_ms(200); 
	io_write(&descr->io, buffer_setup, 1);
	io_read(&descr->io, buffer_read, 2);
	
	if (buffer_setup[1]!=buffer_read[0] || buffer_setup[2]!=buffer_read[1])
	{
		return MCP980X_ERROR;
	}
	return MCP980X_ERROR_NONE; 
}

int16_t _mcp980x_set_tupper(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set)
{	
	struct i2c_m_sync_desc *descr = (struct i2c_m_sync_desc *)(me->io);
	
	uint8_t buffer_read[2];
	uint8_t buffer_temp_upper [3];	

	int16_t temp_int;
	float   temp_float;  
	
	memset(buffer_temp_upper,0,sizeof(buffer_temp_upper));
	
	buffer_temp_upper[0]=MCP980X_ALERT_TUPPER_REG; 
	
	temp_int=(int16_t)temp_set->mcp980x->tupper;
	temp_float=temp_set->mcp980x->tupper;
	 
	if (temp_int>>15)  //if is negative write sing and convert to pozitive 
	{
		buffer_temp_upper[1]|=0b0010000;
		temp_int=temp_int*-1;
		temp_float=temp_set->mcp980x->tupper*-1;  
	}
	buffer_temp_upper[1] = temp_int >> 4;     //move to fit in register   
	buffer_temp_upper[2] = temp_int << 4;       //move to fit in register   
	
	temp_int = (temp_float-(int)temp_float)*100; //prepare data for resolution 
	
	if (temp_int<87&&temp_int>62)
	{
		buffer_temp_upper[2]|=0b00001100;
	}
	else if (temp_int<62&&temp_int>48)
	{
		buffer_temp_upper[2]|=0b00001000;
	}
	else if (temp_int<48&&temp_int>13)
	{
		buffer_temp_upper[2]|=0b00000100;
	}
	
	io_write(&descr->io, buffer_temp_upper, 3);
	
	io_write(&descr->io, buffer_temp_upper, 1);
	io_read(&descr->io, buffer_read, 2);
	if (buffer_temp_upper[1]!=buffer_read[0] || buffer_temp_upper[2]!=buffer_read[1])
	{
		return MCP980X_ERROR;
	}
	return MCP980X_ERROR_NONE; 
}

int16_t _mcp980x_set_lower(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set)
{	
	struct i2c_m_sync_desc *descr = (struct i2c_m_sync_desc *)(me->io);
	
	uint8_t buffer_read[2];
	uint8_t buffer_temp_lower [3];	

	int16_t temp_int;
	float   temp_float;  
	
	memset(buffer_temp_lower,0,sizeof(buffer_temp_lower));
	
	buffer_temp_lower[0]=MCP980X_ALERT_TLOWER_REG; 
	
	temp_int=(int16_t)temp_set->mcp980x->lower;
	temp_float=temp_set->mcp980x->lower;
	 
	if (temp_int>>15)  //if is negative write sing and convert to pozitive 
	{
		buffer_temp_lower[1]|=0b0010000;
		temp_int=temp_int*-1;
		temp_float=temp_set->mcp980x->tupper*-1;  
	}
	buffer_temp_lower[1] = temp_int >> 4;     //move to fit in register   
	buffer_temp_lower[2] = temp_int << 4;       //move to fit in register   
	
	temp_int = (temp_float-(int)temp_float)*100; //prepare data for resolution 
	
	if (temp_int<87&&temp_int>62)
	{
		buffer_temp_lower[2]|=0b00001100;
	}
	else if (temp_int<62&&temp_int>48)
	{
		buffer_temp_lower[2]|=0b00001000;
	}
	else if (temp_int<48&&temp_int>13)
	{
		buffer_temp_lower[2]|=0b00000100;
	}
	
	io_write(&descr->io, buffer_temp_lower, 3);
	
	io_write(&descr->io, buffer_temp_lower, 1);
	io_read(&descr->io, buffer_read, 2);
	if (buffer_temp_lower[1]!=buffer_read[0] || buffer_temp_lower[2]!=buffer_read[1])
	{
		return MCP980X_ERROR;
	}
	return MCP980X_ERROR_NONE; 
}

int16_t _mcp980x_set_critical(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set)
{	
	struct i2c_m_sync_desc *descr = (struct i2c_m_sync_desc *)(me->io);
	
	uint8_t buffer_read[2];
	uint8_t buffer_temp_critical [3];	

	int16_t temp_int;
	float   temp_float;  
	
	memset(buffer_temp_critical,0,sizeof(buffer_temp_critical));
	
	buffer_temp_critical[0]=MCP980X_ALERT_TLOWER_REG; 
	
	temp_int=(int16_t)temp_set->mcp980x->critical;
	temp_float=temp_set->mcp980x->critical;
	 
	if (temp_int>>15)  //if is negative write sing and convert to pozitive 
	{
		buffer_temp_critical[1]|=0b0010000;
		temp_int=temp_int*-1;
		temp_float=temp_set->mcp980x->tupper*-1;  
	}
	buffer_temp_critical[1] = temp_int >> 4;     //move to fit in register   
	buffer_temp_critical[2] = temp_int << 4;       //move to fit in register   
	
	temp_int = (temp_float-(int)temp_float)*100; //prepare data for resolution 
	
	if (temp_int<87&&temp_int>62)
	{
		buffer_temp_critical[2]|=0b00001100;
	}
	else if (temp_int<62&&temp_int>48)
	{
		buffer_temp_critical[2]|=0b00001000;
	}
	else if (temp_int<48&&temp_int>13)
	{
		buffer_temp_critical[2]|=0b00000100;
	}
	
	io_write(&descr->io, buffer_temp_critical, 3);
	
	io_write(&descr->io, buffer_temp_critical, 1);
	io_read(&descr->io, buffer_read, 2);
	if (buffer_temp_critical[1] != buffer_read[0] || buffer_temp_critical[2]!=buffer_read[1])
	{
		return MCP980X_ERROR;
	}
	return MCP980X_ERROR_NONE; 
}

int16_t _mcp980x_set_resolution(struct temperature_sensor *const me,struct tempereture_sensor_settings *temp_set){
	struct i2c_m_sync_desc *descr = (struct i2c_m_sync_desc *)(me->io);
	
	uint8_t buffer_read[2]; 
	uint8_t buffer_resolution[3]; 
	

	memset(buffer_resolution,0,sizeof(buffer_resolution));

	buffer_resolution[0] = MCP980X_RESOLUTION_REG; 
	buffer_resolution[2] = temp_set->mcp980x->mcp980x_resolution;
	 
	io_write(&descr->io, buffer_resolution, 3);
	
	io_write(&descr->io, buffer_resolution, 1);
	io_read(&descr->io, buffer_resolution, 2);
	if (buffer_resolution[1]!=buffer_read[0] || buffer_resolution[2]!=buffer_read[1])
	{
		return MCP980X_ERROR;
	}
	return MCP980X_ERROR_NONE; 
}