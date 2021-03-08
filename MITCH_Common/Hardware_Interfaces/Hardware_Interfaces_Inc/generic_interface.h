/*
 * generic_interface.h
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */

#ifndef HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_GENERIC_INTERFACE_H_
#define HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_GENERIC_INTERFACE_H_

#include "interface_structs.h"
#include <stdint.h>
#include <stdbool.h>

/* Enum */

typedef enum {
	GPS_MT3339,
	IMU_ICM20948,
	BMP_MS5607,
	IMU_MMA1211
} DeviceType_t;


/* Struct Definitions */

//Generic
typedef struct genericIMU genericIMU_t;
typedef struct genericGPS genericGPS_t;
typedef struct genericBMP genericBMP_t;
//IMU
typedef struct ICM20948 ICM20948_t;
typedef struct MMA1211 MMA1211_t;
//GPS
typedef struct MT3339 MT3339_t;
//BMP
typedef struct MS5607 MS5607_t;


/* Separate IMU Structs */

typedef struct ICM20948 {
	int16_t accel_xout;
	int16_t accel_yout;
	int16_t accel_zout;
	int16_t gyr_xout;
	int16_t gyr_yout;
	int16_t gyr_zout;
	int16_t mag_xout;
	int16_t mag_yout;
	int16_t mag_zout;
} ICM20948_t;

typedef struct MMA1211 {
	int16_t accel_zout;
} MMA1211_t;


/* Separate GPS Structs */

typedef struct MT3339 {
	char gpsString[MAX_NMEA];
} MT3339_t;


/* Separate BMP Structs */

typedef struct MS5607 {
	int16_t pressure;
	int16_t temperature;
} MS5607_t;


/* Generic Struct Declarations */

//IMU
typedef struct genericIMU {
	uint8_t imuType;
	union {
		ICM20948_t ICM20948;
		MMA1211_t MMA1211;
		//To be filled
	};

} genericIMU_t;

//GPS
typedef struct genericGPS {
	uint8_t gpsType;
	union {
		MT3339_t MT3339;
		//To be filled
	};

} genericGPS_t;

void gpsInit(bool *gpsNominal);
void gpsLoadString(char* gpsNmea);

//BMP
typedef struct genericBMP {
	uint8_t bmpType;
	union {
		MS5607_t MS5607;
		//To be filled
	};

} genericBMP_t;


#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_GENERIC_INTERFACE_H_ */
