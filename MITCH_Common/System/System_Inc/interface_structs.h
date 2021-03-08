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


#endif /* SYSTEM_SYSTEM_INC_INTERFACE_STRUCTS_H_ */
