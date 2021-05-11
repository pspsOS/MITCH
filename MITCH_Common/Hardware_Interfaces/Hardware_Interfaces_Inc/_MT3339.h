/*
 * _MT3339.h
 *
 *  Created on: Apr 6, 2021
 *      Author: Jeff
 */

#ifndef HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC__MT3339_H_
#define HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC__MT3339_H_

#include "generic_interface.h"

#define BUF(B) ((uint8_t*) &(B.buffer[B.i]))

typedef struct {
	char buffer[256];
	uint8_t i;
} _NMEA_Buffer_t;



#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC__MT3339_H_ */
