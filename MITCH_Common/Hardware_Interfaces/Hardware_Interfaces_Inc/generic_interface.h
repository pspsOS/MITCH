/*
 * generic_interface.h
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */

#ifndef HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_GENERIC_INTERFACE_H_
#define HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_GENERIC_INTERFACE_H_

#include "system_functions.h"
#include "interface_structs.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>



/** Checks/Sets NO_HAL_DEF Flag **/
#if !defined(__STM32F4xx_HAL_DEF)
	typedef enum {
	  HAL_OK       = 0x00U,
	  HAL_ERROR    = 0x01U,
	  HAL_BUSY     = 0x02U,
	  HAL_TIMEOUT  = 0x03U
	} HAL_StatusTypeDef;
	#define __NO_HAL_DEF
#endif


/** Checks/Sets NO_STM_DEV Flag **/
#if !defined(__STM32F411xE_H)
	typedef void GPIO_TypeDef;
	#define __NO_STM_DEV
#endif

/** Checks/Sets NO_HAL_SPI Flag **/
#if !defined (STM32F4xx_HAL_SPI_H) || defined(__NO_HAL_DEF) || defined(__NO_STM_DEV)
	typedef void SPI_HandleTypeDef;
	#define __NO_HAL_SPI
#endif
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
	//Baro Data
		uint16_t senst1;		//C1 on datasheet
		uint16_t offt1; 		//C2 on datasheet
		uint16_t tcs;			//C3 on datasheet
		uint16_t tco;			//C4 on datasheet
		uint16_t tref;			//C5 on datasheet
		uint16_t tempsens;		//C6 on datasheet
		uint32_t digitalPres;	//D1 on datasheet (Only 24 bits will be filled)
		uint32_t digitalTemp;	//D2 on datasheet (Only 24 bits will be filled)
		int32_t	deltaT;			//dT on datasheet (This is a calculated value)
		int32_t temp;			//TEMP on datasheet
		int64_t off;			//OFF on datasheet (This is a calculated value)
		int64_t sens;			//SENS on datasheet (This is a calculated value)
		int32_t pressure;		//P on datasheet (This is a calculated value)
	// SPI Interface
		SPI_HandleTypeDef *bus;
		GPIO_TypeDef *port;
		uint16_t pin;
		HAL_StatusTypeDef state;
} MS5607_t;


/* Generic Struct Declarations */


typedef union {
	ICM20948_t ICM20948;
	MMA1211_t MMA1211;
	MT3339_t MT3339;
	MS5607_t MS5607;
} Device_u;

typedef HAL_StatusTypeDef (*read_fun)(Device_u*);

typedef struct genericDevice {
	DeviceType_t deviceType;
	read_fun read;
	Device_u device;
} genericDevice_t;


HAL_StatusTypeDef sendSPI(uint8_t * cmd, int len, GPIO_TypeDef * port, uint16_t pin, SPI_HandleTypeDef *bus, DeviceType_t device);
HAL_StatusTypeDef receiveSPI(uint8_t * cmd, int cmdLen, uint8_t * data, int dataLen, GPIO_TypeDef * port, uint16_t pin, SPI_HandleTypeDef *bus, DeviceType_t device);
void handleSPI(HAL_StatusTypeDef state, DeviceType_t device);



#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_GENERIC_INTERFACE_H_ */
