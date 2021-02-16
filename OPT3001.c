/*
 * OPT3001.c
 *
 *  Created on: 15/02/2021
 *      Author: edgar
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "bsp.h"        // board support package
#include "OPT3001.h"

//void extern GetAmbientLight(*uint_16 raw_data){
//    uint8_t data_HL[0] = 0x00;   // buffer to receive data
//
//
//}

void extern ConfigSensor(){

    uint8_t bffConf[2] = { 0xDE, 0xAD };    // 16 bit register to save configuration register values
    uint16_t ConfgSeq = 0 ;

    ConfgSeq = (AUTO_FS | CT_800ms | CONT_CONV) ;

//    bffConf[0] = (uint8_t)((ConfgSeq & 0xFF00) >> 8 ); // MSB
//    bffConf[1] = (uint8_t)(ConfgSeq & 0x00FF); // LSB

    BSP_u32_I2CDatSendSensors(OPT3001_SLV_ADD, CONFIG, 2, bffConf);
}
