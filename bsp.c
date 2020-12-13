/*
 * bsp.c
 *
 * Board Support Package (BSP) for the TM4C123GXL board
 *
 *
 *	Here goes all the hardware configuration inherent to the hardware (microcontroller)
 *
 *	 Created on: 13/12/2020
 *      Author: edgar_jd
 */



#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "utils/uartstdio.h"
#include "bsp.h"

// core initialization
void BSP_init(void){

	// Clock at 80MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
}


uint32_t BSP_InitI2C01(void){
    //Activation of modules related to I2C1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);        // Enable port B for I2C pin
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1)){ // Wait for the I2C0 module to be ready.
    }
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);

    // Configure the pin muxing for I2C1 functions on PortA[7:6]
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    // Select the I2C functions for these pins
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

    // Initialize the I2C1 master module at 400kbps. Use the system clock for
    // the I2C0 module.
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), true);

    return 1;
}

