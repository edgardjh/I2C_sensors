/*
 * bsp.h
 *
 * Board Support Package (BSP) for the TM4C123GXL board
 *
 *
 *	Here goes all the hardware configuration inherent to the hardware (microcontroller)
 *
 *	 Created on: 13/12/2020
 *      Author: edgar_jd
 */

#ifndef BSP_H_
#define BSP_H_



//*****************************************************************************
//
// Function prototypes.
//
//*****************************************************************************

extern void BSP_init(void);

extern uint32_t BSP_InitI2C01(void);
extern uint32_t BSP_u32_MtBusyErrSR( void);
extern uint32_t	BSP_u32_I2CDatRecvSensors(uint8_t slave_addr, uint8_t slave_reg, uint8_t num_dat, uint8_t *ptr_bff);
extern uint32_t	BSP_u32_I2CDatSendSensors(uint8_t slave_addr, uint8_t slave_reg, uint8_t num_dat, uint8_t *ptr_bff);
extern void BSP_I2CBusReset(void);






#endif /* BSP_H_ */
