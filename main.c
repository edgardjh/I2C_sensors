
/**
 *
 * main.c
 * This project is going to be use to test i2c communications whit the "sensors BooserPack" and
 * the GY-521 board sensors.
 *
 */



#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "bsp.h"
#include "driverlib/sysctl.h"
#include "driverlib/i2c.h"
#include "inc/hw_memmap.h"
#include "OPT3001.h"

uint8_t buffer_rec[2] = {0xDE, 0xAD};
uint16_t raw_data = 0;
uint16_t exp = 0;
float lux = 0;

int main(void){

	// Board Configurations
	BSP_init();
	BSP_InitI2C01();    // Initialized I2C_01 peripherical, (PORTA.6 -> SCL (clk), PORTA.7 ->  SDA)

	SysCtlDelay(100);   // Delay

	BSP_I2CBusReset();

	SysCtlDelay(100);    // Delay


	ConfigSensor();     // continuous operation

	while(1){
	    BSP_u32_I2CDatRecvSensors(OPT3001_SLV_ADD, RESULT, 2, buffer_rec);

	    raw_data = ( (buffer_rec[0]<<8) | buffer_rec[1]);
	    exp =  (raw_data >> 12) & 0x0F;
	    exp = (1 << exp);
	    raw_data = raw_data & 0x0FFF;
	    lux = (float)(0.01*exp*raw_data);

	    SysCtlDelay(250000);    // Delay
	}

	while(1);

	return 0;
}
