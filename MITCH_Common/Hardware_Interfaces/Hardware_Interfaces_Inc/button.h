/*
 * button.h
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#ifndef NUCLEOBUTTON_H_
#define NUCLEOBUTTON_H_

#include "generic_interface.h"


#define _BUTTON_INV_MASK	(uint8_t)(0b00010000) // Invert Input


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

uint8_t _getINV(genericDevice_t* device);
void _setINV(genericDevice_t* device);
void _clrINV(genericDevice_t* device);
uint8_t _getHSF(genericDevice_t* device);
void _setHSF(genericDevice_t* device);
void _clrHSF(genericDevice_t* device);
uint8_t _getHRF(genericDevice_t* device);
void _setHRF(genericDevice_t* device);
void _clrHRF(genericDevice_t* device);
bool _getBChange(genericDevice_t* device);
void _setBChange(genericDevice_t* device);
void _clrBChange(genericDevice_t* device);
bool _getBValue(genericDevice_t* device);
void _setBValue(genericDevice_t* device);
void _clrBValue(genericDevice_t* device);

uint8_t _getBMode(genericDevice_t* device);
void _setBMode(genericDevice_t* device, ButtonMode_t mode);

#ifndef NO_BUTTON_FUNCTIONS


button_fun _getBSF(genericDevice_t* device);
void _setBSF(genericDevice_t* device, button_fun set_fun);
void _clrBSF(genericDevice_t* device);
button_fun _getBRF(genericDevice_t* device);
void _setBRF(genericDevice_t* device, button_fun reset_fun);
void _clrBRF(genericDevice_t* device);
// Default Button functions
void __no_fun();
#endif
#endif /* NUCLEOBUTTON_H_ */
