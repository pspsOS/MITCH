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



/* Enum */

typedef enum {
	GPIO_BUTTON,
	GPS_MT3339,
	IMU_ICM20948,
	BMP_MS5607,
	IMU_MMA1211
} SensorType_t;


typedef enum {
	GPIO_PIN,
	SPI_INTERFACE,
	UART_INTERFACE,
	I2C_INTERFACE
} InterfaceType_t;

/* Struct Definitions */

/** Interfaces **/
typedef bool InterfaceLock_t;

typedef struct PIN PIN_t;
typedef struct SPI SPI_t;
typedef struct UART UART_t;
typedef struct I2C I2C_t;
typedef union Interface Interface_u;

typedef struct PIN {
	GPIO_TypeDef *port;
	uint16_t pin;
} PIN_t;

typedef struct SPI {
	SPI_HandleTypeDef *bus;
	GPIO_TypeDef *port;
	uint16_t pin;
	uint32_t timeout;
	//uint32_t retryDelay;
} SPI_t;

// TODO: UART Struct
typedef struct UART {
	UART_HandleTypeDef *huart;
} UART_t;
// TODO: I2C Struct
typedef struct I2C {} I2C_t;

typedef union Interface {
	PIN_t PIN;
	SPI_t SPI;
	UART_t UART;
	I2C_t I2C;
} Interface_u;


/** Sensors **/
//Button
typedef struct button button_t;

//IMU
typedef struct ICM20948 ICM20948_t;
typedef struct MMA1211 MMA1211_t;
//GPS
typedef struct MT3339 MT3339_t;
//BMP
typedef struct MS5607 MS5607_t;
//Generic
typedef struct genericSensor genericSensor_t;


typedef struct button {
	/**  status = 00000ICV
	 I = Invert input
	 C = Change
	 V = Value
	 */
	uint8_t status;
} button_t;


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
} MS5607_t;


/* Generic Struct Declarations */


typedef union {
	button_t button;
	ICM20948_t ICM20948;
	MMA1211_t MMA1211;
	MT3339_t MT3339;
	MS5607_t MS5607;
} Sensor_u;

typedef uint8_t (*read_fun)(volatile genericSensor_t*);

typedef struct genericSensor {
	SensorType_t sensorType;
	read_fun read;
	Sensor_u sensor;
	Interface_u interface;
	HAL_StatusTypeDef state;

	bool hasUpdate;
	bool lock;
} genericSensor_t;




/** Outputs **/
typedef struct LED LED_t;

typedef struct LED {
	uint8_t status;
	PIN_t PIN;
} LED_t;


HAL_StatusTypeDef sendSPI(genericSensor_t* sensor, uint8_t* cmd, int cmdlen);
HAL_StatusTypeDef receiveSPI(genericSensor_t* sensor, uint8_t* cmd, int cmdlen, uint8_t * data, int datalen);
HAL_StatusTypeDef interfaceLock(InterfaceLock_t* lock, uint32_t retryDelay, uint32_t timeout);
HAL_StatusTypeDef interfaceUnlock(InterfaceLock_t* lock, genericSensor_t* sensor);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_GENERIC_INTERFACE_H_ */
