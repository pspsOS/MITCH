/*
 * NucleoButton.h
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#ifndef NUCLEOBUTTON_H_
#define NUCLEOBUTTON_H_

#include "generic_interface.h"

#define _BUTTON_HSF_MASK	(0b00001000) // Has Reset Function Mask
#define _BUTTON_HRF_MASK	(0b00000100) // Has Set Function Mask
#define _BUTTON_MODE_MASK	(0b00000010) // Mode Mask
#define _BUTTON_STATE_MASK	(0b00000001) // State Mask

typedef enum {
	ON_CHANGE = 0,
	ON_VALUE = 1
} ButtonMode_t;

genericDevice_t button_init(GPIO_TypeDef *port, uint16_t pin);
HAL_StatusTypeDef button_read(genericDevice_t* device);

uint8_t _setHSF(uint8_t status);
uint8_t _clrHSF(uint8_t status);
uint8_t _setHRF(uint8_t status);
uint8_t _clrHRF(uint8_t status);
uint8_t _setBMode(uint8_t status, ButtonMode_t mode);
uint8_t _setBState(uint8_t status);
uint8_t _rstBState(uint8_t status);
uint8_t _setBStateVal(uint8_t status, GPIO_PinState state);

#endif /* NUCLEOBUTTON_H_ */
