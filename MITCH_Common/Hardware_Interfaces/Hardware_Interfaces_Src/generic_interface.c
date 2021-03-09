/*
 * generic_interface.c
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */


#include "generic_interface.h"

HAL_StatusTypeDef sendSPI(uint8_t * cmd, int len, GPIO_TypeDef * port, uint16_t pin, SPI_HandleTypeDef *bus, DeviceType_t device) {
	HAL_StatusTypeDef state = HAL_ERROR;
#ifndef __NO_HAL_SPI
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET); //CS low
	state = HAL_SPI_Transmit(bus, cmd, len, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);	//CS high
#endif
	handleSPI(state, device);
	return state;
}

HAL_StatusTypeDef receiveSPI(uint8_t * cmd, int cmdLen, uint8_t * data, int dataLen, GPIO_TypeDef * port, uint16_t pin, SPI_HandleTypeDef *bus, DeviceType_t device) {
	//Note: dataLen should be number of bytes in the register group being read
	HAL_StatusTypeDef state = HAL_ERROR;
#ifndef __NO_HAL_SPI
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET); //CS low
	state = HAL_SPI_Transmit(bus, cmd, cmdLen, HAL_MAX_DELAY);
	HAL_SPI_Receive(bus, data, dataLen, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);	//CS high
#endif
	handleSPI(state, device);
	return state;
}


uint8_t bmpRead(genericBMP_t* bmp) {
return 0;
}


void handleSPI(HAL_StatusTypeDef state, DeviceType_t device) {
}

