/*
 * generic_interface.c
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */


#include "generic_interface.h"



/** Sensor, InterfaceLock should already be locked. CS Pin is left low.  **/
HAL_StatusTypeDef sendSPI(genericSensor_t* sensor, uint8_t* cmd, int cmdlen) {



#ifndef __NO_HAL_SPI
	// Declares convenient SPI pointer
	SPI_t* SPI = &(sensor->interface.SPI);
	// SPI Transmission

	// Sends cmd
	sensor->state = HAL_SPI_Transmit(SPI->bus, cmd, cmdlen, SPI->timeout);
#endif

	// Returns sensor state
	return sensor->state;
}

HAL_StatusTypeDef receiveSPI(genericSensor_t* sensor, uint8_t* cmd, int cmdlen, uint8_t * data, int datalen) {


#ifndef __NO_HAL_SPI

	SPI_t *SPI = &(sensor->interface.SPI);
	sensor->state = HAL_SPI_Transmit(SPI->bus, cmd, cmdlen, SPI->timeout);

	if(sensor->state == HAL_OK)
	sensor->state = HAL_SPI_Receive(SPI->bus, data, datalen, SPI->timeout);


#endif
	return sensor->state;
}

HAL_StatusTypeDef interfaceLock(InterfaceLock_t* lock, uint32_t retryDelay, uint32_t timeout) {
	uint32_t tickstart = getTimeStamp();
	while(*lock) {
		if(((getTimeStamp() - tickstart) >= timeout) && ((timeout != HAL_MAX_DELAY) || timeout == 0))
			return HAL_TIMEOUT;
		retryTakeDelay(retryDelay);
	}
	*lock = true;
	return HAL_OK;
}

HAL_StatusTypeDef interfaceUnlock(InterfaceLock_t* lock, genericSensor_t* sensor) {
	*lock = false;
	return sensor->state;
}



