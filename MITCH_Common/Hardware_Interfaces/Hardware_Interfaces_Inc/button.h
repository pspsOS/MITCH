/*
 * button.h
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#ifndef NUCLEOBUTTON_H_
#define NUCLEOBUTTON_H_

#include "generic_interface.h"


#define _BUTTON_INV_MASK		(uint8_t)(0b00010000) // Invert Input
#define _BUTTON_RTOGGLE_MASK 	(uint8_t)(0b00001000) // Rising Toggle Mask
#define _BUTTON_FTOGGLE_MASK 	(uint8_t)(0b00000100) // Falling Toggle Mask
#define _BUTTON_CHANGE_MASK		(uint8_t)(0b00000010) // Change Mask
#define _BUTTON_VALUE_MASK		(uint8_t)(0b00000001) // Value Mask
#define _BUTTON_STATE_MASK (uint8_t) (_BUTTON_CHANGE_MASK | _BUTTON_VALUE_MASK)


typedef enum {
	BUTTON_RESET = GPIO_PIN_RESET,
	BUTTON_SET = GPIO_PIN_SET,
	BUTTON_RISING,
	BUTTON_FALLING,
} ButtonState_t;

genericSensor_t button_init(GPIO_TypeDef *port, uint16_t pin);
uint8_t button_read(genericSensor_t* sensor);
ButtonState_t button_GetState(genericSensor_t* sensor);
void button_Invert(genericSensor_t* sensor);

bool button_OnSet(genericSensor_t* sensor);
bool button_OnReset(genericSensor_t* sensor);
bool button_OnRising(genericSensor_t* sensor);
bool button_OnFalling(genericSensor_t* sensor);
bool button_OnRToggle(genericSensor_t* sensor);
bool button_OnFToggle(genericSensor_t* sensor);


bool _getBINV(genericSensor_t* sensor);
void _setBINV(genericSensor_t* sensor);
void _clrBINV(genericSensor_t* sensor);

bool _getRToggle(genericSensor_t* sensor);
void _setRToggle(genericSensor_t* sensor);
void _clrRToggle(genericSensor_t* sensor);
void _doRToggle(genericSensor_t* sensor);

bool _getFToggle(genericSensor_t* sensor);
void _setFToggle(genericSensor_t* sensor);
void _clrFToggle(genericSensor_t* sensor);
void _doFToggle(genericSensor_t* sensor);

bool _getBChange(genericSensor_t* sensor);
void _setBChange(genericSensor_t* sensor);
void _clrBChange(genericSensor_t* sensor);
bool _getBValue(genericSensor_t* sensor);
void _setBValue(genericSensor_t* sensor);
void _clrBValue(genericSensor_t* sensor);

uint8_t _getBStatus(genericSensor_t* sensor);


#endif /* NUCLEOBUTTON_H_ */
