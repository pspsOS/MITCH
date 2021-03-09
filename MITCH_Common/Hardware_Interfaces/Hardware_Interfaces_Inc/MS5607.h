/*
 * MS5607.h
 *
 *  Created on: Mar 8, 2021
 *      Author: Jeff
 */

#ifndef MS5607_H_
#define MS5607_H_

#include "generic_interface.h"

#define D1_256			0x40
#define	D1_512			0x42
#define D1_1024			0x44
#define	D1_2048			0x46
#define	D1_4096			0x48
#define D2_256			0x50
#define D2_512			0x52
#define D2_1024			0x54
#define D2_2048			0x56
#define D2_4069			0x58
#define CONV_T_256		1 //Conversion times are worst case rounded up
#define CONV_T_512		2
#define CONV_T_1024		3
#define CONV_T_2048 	5
#define CONV_T_4096 	10


genericBMP_t MS5607_init(SPI_HandleTypeDef *bus, GPIO_TypeDef *port, uint16_t pin);

#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_MS5607_H_ */
