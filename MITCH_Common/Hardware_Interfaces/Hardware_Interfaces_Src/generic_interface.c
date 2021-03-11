/*
 * generic_interface.c
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */


#include "generic_interface.h"



HAL_StatusTypeDef sendSPI(genericDevice_t* device, uint8_t* cmd, int cmdlen) {
	device->state = HAL_ERROR;
	SPI_t *SPI = &(device->interface.SPI);
#ifndef __NO_HAL_SPI
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_RESET);
	device->state = HAL_SPI_Transmit(SPI->bus, cmd, cmdlen, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_SET);
#endif
	return device->state;
}

HAL_StatusTypeDef receiveSPI(genericDevice_t* device, uint8_t* cmd, int cmdlen, uint8_t * data, int datalen) {
	device->state = HAL_ERROR;
	SPI_t *SPI = &(device->interface.SPI);
#ifndef __NO_HAL_SPI
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_RESET);
	device->state = HAL_SPI_Transmit(SPI->bus, cmd, cmdlen, HAL_MAX_DELAY);
	if(device->state == HAL_OK) device->state = HAL_SPI_Receive(SPI->bus, data, datalen, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_SET);
#endif
	return device->state;
}

