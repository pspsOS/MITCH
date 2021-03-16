/*
 * interface_structs.h
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */

#ifndef SYSTEM_SYSTEM_INC_INTERFACE_STRUCTS_H_
#define SYSTEM_SYSTEM_INC_INTERFACE_STRUCTS_H_

#include "main.h"
#include "STM.h"

#include <stdint.h>
#include <stdbool.h>

#define MAX_NMEA (80)

typedef enum {
	LOCKED,
	HAS_UPDATE,
	UNLOCKED
} Status_t;

typedef struct gpsData {
	uint32_t timeStamp;
	char nmeaGGA[MAX_NMEA];
	char nmeaRMC[MAX_NMEA];
	uint8_t fix;
	float alt;
	float speed;
	int utc;
	bool hasUpdate;
	bool lock;
} gpsData_t;


typedef struct {
	uint32_t timeStamp;
	HAL_StatusTypeDef state;
	int32_t pressure;     // MIN: 1000, MAX: 120000, VALUE: 110002 = 1100.02 mbar
	int32_t temperature;  // MIN:-4000, MAX: 8500,   VALUE: 2000 = 20.00 degC
	bool hasUpdate;
	bool lock;
} bmpData_t;

#endif /* SYSTEM_SYSTEM_INC_INTERFACE_STRUCTS_H_ */
