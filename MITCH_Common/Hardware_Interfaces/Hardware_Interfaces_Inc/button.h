/*
 * button.h
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#ifndef NUCLEOBUTTON_H_
#define NUCLEOBUTTON_H_

#include "generic_interface.h"


#define _BUTTON_INV_MASK	(uint8_t)(0b00000100) // Invert Input
#define _BUTTON_CHANGE_MASK (uint8_t)(0b00000010) // Change Mask
#define _BUTTON_VALUE_MASK	(uint8_t)(0b00000001) // Value Mask
#define _BUTTON_STATE_MASK (uint8_t) (_BUTTON_CHANGE_MASK | _BUTTON_VALUE_MASK)


typedef enum {
	BUTTON_RESET = GPIO_PIN_RESET,
	BUTTON_SET = GPIO_PIN_SET,
	BUTTON_RISING,
	BUTTON_FALLING,
} ButtonState_t;

genericDevice_t button_init(GPIO_TypeDef *port, uint16_t pin);
uint8_t button_read(genericDevice_t* device);
ButtonState_t button_getState(genericDevice_t* device);

bool _getINV(genericDevice_t* device);
void _setINV(genericDevice_t* device);
void _clrINV(genericDevice_t* device);
bool _getBChange(genericDevice_t* device);
void _setBChange(genericDevice_t* device);
void _clrBChange(genericDevice_t* device);
bool _getBValue(genericDevice_t* device);
void _setBValue(genericDevice_t* device);
void _clrBValue(genericDevice_t* device);

uint8_t _getBStatus(genericDevice_t* device);


#endif /* NUCLEOBUTTON_H_ */
