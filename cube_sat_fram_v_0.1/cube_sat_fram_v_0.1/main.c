#include <atmel_start.h>
#include "temperature_sensor_main.h"
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	temperature_sensors_init();
	/* Replace with your application code */
	while (1) {
	int x = temperature_sensor_read(TEMPERATURE_SENSOR); 
		delay_ms(1000); 
	}
}
