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


//*****************************************************************************
//
// Read the state of the master ad detects errors.
//
//*****************************************************************************
extern uint32_t BSP_u32_MtBusyErrSR( void){
	while(I2CMasterBusy(I2C1_BASE));									// Waiting for master
	if(I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE){					// A error detected¡¡ stop receiving
			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);
			return 1;
		}

	// not error detected & master free
	return 0;
}

/*
 * Read a specific register on slave device
 */
extern uint32_t	BSP_u32_I2CDatRecvSensors(uint8_t slave_addr, uint8_t slave_reg, uint8_t num_data, uint8_t (*ptr_bff)[NULL]){
	uint8_t idx = 0;
	// Writing to slave the register to be read
	I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false); 		// Set the slave address to I2CMSA [7:1] and the R/_S  bit[0] to low (Send/transmit)
	I2CMasterDataPut(I2C1_BASE, slave_reg);						// Specify register to be read
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);	// Send control byte and register address byte to slave device
	BSP_u32_MtBusyErrSR();

	I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);				// Set the slave address to I2CMSA [7:1] and the R/_S  bit[0] to high  (Send/transmit)
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);	// Write ---01011 to I2CMCS
	for(idx = 0 ; idx < num_data; idx++){
		if(BSP_u32_MtBusyErrSR()){									// Waiting to get the data
			return 1;											// error detected;
		}
		(*ptr_bff)[idx] = I2CMasterDataGet(I2C1_BASE);		// Return data pulled from the specified register
		I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);	// Write ---0-001 to I2CMCS
	}

	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);	// Write ---0-001 to I2CMCS
	BSP_u32_MtBusyErrSR();

	// not error detected & master free
	return 0;
}

/*
 * Write a specific register on slave device
 */
extern uint32_t	BSP_u32_I2CDatSendSensors(uint8_t slave_addr, uint8_t slave_reg, uint8_t num_dat, uint8_t (*ptr_bff)[NULL]){
	uint8_t idx = 0;
	I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);	// Set the slave address to I2CMSA [7:1] and the R/_S  bit[0] to low (Send/transmit)

	// sending the register address
	I2CMasterDataPut(I2C1_BASE, slave_reg);							// Write data to I2CMDR
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);	// Write ---0-011 to I2CMCS
	BSP_u32_MtBusyErrSR();

	for(idx = 0; idx < num_dat; idx++){
		I2CMasterDataPut(I2C1_BASE, (*ptr_bff)[idx]);					// Write data to I2CMDR
		I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);	// Write ---0-001 to I2CMCS
		if(BSP_u32_MtBusyErrSR()){											// Waiting to get data
			return 1;													// A error de detected
		}

	}

	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);	// Write ---0-101 to I2CMCS
	BSP_u32_MtBusyErrSR();
	// not error detected & master free
	return 0;
}
