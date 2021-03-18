/*
 * button.h
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#ifndef NUCLEOBUTTON_H_
#define NUCLEOBUTTON_H_

#include "generic_interface.h"

#define _BUTTON_MODE_MASK	(0b00010000) // Mode Mask
#define _BUTTON_INV_MASK	(0b00001000) // Invert Input
#define _BUTTON_HSF_MASK	(0b00000100) // Has Reset Function Mask
#define _BUTTON_HRF_MASK	(0b00000010) // Has Set Function Mask
#define _BUTTON_STATE_MASK	(0b00000001) // State Mask

#define _BUTTON_MODE_CHANGE (0b00000000)
#define _BUTTON_MODE_VALUE	(0b00010000)

typedef enum {
	ON_CHANGE = 0,
	ON_VALUE = 1
} ButtonMode_t;

genericDevice_t button_init(GPIO_TypeDef *port, uint16_t pin);
uint8_t button_read(genericDevice_t* device);

// TODO: Make functions use genericDevice_t and pointers
uint8_t _getINV(uint8_t status);
uint8_t _setINV(uint8_t status);
uint8_t _clrINV(uint8_t status);
uint8_t _getHSF(uint8_t status);
uint8_t _setHSF(uint8_t status);
uint8_t _clrHSF(uint8_t status);
uint8_t _getHRF(uint8_t status);
uint8_t _setHRF(uint8_t status);
uint8_t _clrHRF(uint8_t status);
uint8_t _getBMode(uint8_t status);
uint8_t _setBMode(uint8_t status, ButtonMode_t mode);
uint8_t _setBState(uint8_t status);
uint8_t _clrBState(uint8_t status);
//uint8_t _setBStateVal(uint8_t status, GPIO_PinState state);

// Default Button functions
void __no_fun();
#endif /* NUCLEOBUTTON_H_ */
