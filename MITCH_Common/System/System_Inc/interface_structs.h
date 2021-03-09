/*
 * interface_structs.h
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */

#ifndef SYSTEM_SYSTEM_INC_INTERFACE_STRUCTS_H_
#define SYSTEM_SYSTEM_INC_INTERFACE_STRUCTS_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_NMEA (80)

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


typedef struct bmpData {
	uint32_t timeStamp;
	int32_t pressure;     // MIN: 1000, MAX: 120000, VALUE: 110002 = 1100.02 mbar
	int32_t temperature;  // MIN:-4000, MAX: 8500,   VALUE: 2000 = 20.00 degC
	bool hasUpdate;
	bool lock;
} bmpData_t;

#endif /* SYSTEM_SYSTEM_INC_INTERFACE_STRUCTS_H_ */
