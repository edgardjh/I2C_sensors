/*
 * OPT3001.h
 *
 *  Created on: 12/02/2021
 *      Author: Edgar
 *  Registers of OPT3001 are 16 bits lenght
 *
 */

#ifndef OPT3001_H_
#define OPT3001_H_

/*
 * Slave I2C address of the sensor OPT3001
 */
#define OPT3001_SLV_ADD 0x47


/*
 *   Registers addresses
 */
#define RESULT      0x00
#define CONFIG      0x01
#define LOW_LIMIT   0x02
#define HIGH_LIMIT  0x03
#define MAN_ID      0x7E
#define DEV_ID      0x7F


//********************************************************************************************//
// BITS RELATED TO CONFIGURATION REGISTER
//********************************************************************************************//

/*
 *   Full-Scale Range
 *   Configuration register
 *   Lux per LSB
 *   W/R
 */
#define LP_LSB_001  (0x00 << 12)
#define LP_LSB_002  (0x01 << 12)
#define LP_LSB_004  (0x02 << 12)
#define LP_LSB_008  (0x03 << 12)
#define LP_LSB_016  (0x04 << 12)
#define LP_LSB_032  (0x05 << 12)
#define LP_LSB_064  (0x06 << 12)
#define LP_LSB_128  (0x07 << 12)
#define LP_LSB_256  (0x08 << 12)
#define LP_LSB_512  (0x09 << 12)
#define LP_LSB_1024 (0x0A << 12)
#define LP_LSB_2048 (0x0B << 12)
#define AUTO_FS     (0x0C << 12)

/*
 *   Convertion Time
 *   Configuration register
 *   W/R
 */
#define CT_100ms    (0x00 << 11)
#define CT_800ms    (0x01 << 11)

/*
 *   The mode of conversion operation field controls whether the device is operating in continuous
 *   conversion, single-shot, or low-power shutdown mode
 *   Configuration register
 *   W/R
 */
#define SHUTDOWN    (0x00 << 9)
#define SINGLE_SHOT (0x01 << 9)
#define CONT_CONV   (0x02 << 9)

/*
 *  Overflow flag field
 *  Configuration register
 *  R
 */
#define OVF (0x01 << 8)

/*
 *  Conversion ready field
 *  Configuration register
 *  R
 */
#define CRF (0x01 << 7)

/*
 *  Flag high field
 *  Configuration register
 *  R
 */
#define FLG_H (0x01 << 6)

/*
 *  Flag low field
 *  Configuration register
 *  R
 */
#define FLG_L (0x01 << 5)

/*
 *  Latch field
 *  Configuration register
 *  R/W
 */
//#define LF (0x01 << 4)
//#define LF (0x01 << 4)

/*
 *  Polarity field
 *  Configuration register
 *  R/W
 */
#define POL_LOW     (0x00 << 3)
#define POL_HIGH    (0x01 << 3)

/*
 *  Mask exponent field
 *  Configuration register
 *  R/W
 */
//#define ME  (0x00 << 2)
//#define ME  (0x01 << 2)


/*
 *  Fault count field
 *  Configuration register
 *  R/W
 */
#define ONE_FC   (0x00)
#define TWO_FC   (0x01)
#define FOUR_FC  (0x02)
#define EIGHT_FC (0x03)

//********************************************************************************************//
// BITS RELATED TO LOW LIMIT REGISTER
//********************************************************************************************//
/* Low Limit Register*/
#define LM_LE   (0x000F << 12)
#define LM_TL   (0x07FF << 12)

/* Low Limit Register*/
#define HM_HE   (0x000F << 12)
#define HM_TL   (0x07FF << 12)


//********************************************************************************************//
// Functions
//********************************************************************************************//

/* Low Limit Register*/
//void extern GetAmbientLight(*uint_16 raw_data);
//void extern GetManID(*uint_16 ManID);
//void extern GetDeviceID(*uint_16 DevID);
extern void  ConfigSensor();




#endif /* OPT3001_H_ */
