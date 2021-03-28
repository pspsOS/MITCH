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
uint8_t button_read(volatile genericSensor_t* sensor);
ButtonState_t button_GetState(volatile genericSensor_t* sensor);
void button_Invert(volatile genericSensor_t* sensor);

bool button_OnSet(volatile genericSensor_t* sensor);
bool button_OnReset(volatile genericSensor_t* sensor);
bool button_OnRising(volatile genericSensor_t* sensor);
bool button_OnFalling(volatile genericSensor_t* sensor);
bool button_OnRToggle(volatile genericSensor_t* sensor);
bool button_OnFToggle(volatile genericSensor_t* sensor);


bool _getBINV(volatile genericSensor_t* sensor);
void _setBINV(volatile genericSensor_t* sensor);
void _clrBINV(volatile genericSensor_t* sensor);

bool _getRToggle(volatile genericSensor_t* sensor);
void _setRToggle(volatile genericSensor_t* sensor);
void _clrRToggle(volatile genericSensor_t* sensor);
void _doRToggle(volatile genericSensor_t* sensor);

bool _getFToggle(volatile genericSensor_t* sensor);
void _setFToggle(volatile genericSensor_t* sensor);
void _clrFToggle(volatile genericSensor_t* sensor);
void _doFToggle(volatile genericSensor_t* sensor);

bool _getBChange(volatile genericSensor_t* sensor);
void _setBChange(volatile genericSensor_t* sensor);
void _clrBChange(volatile genericSensor_t* sensor);
bool _getBValue(volatile genericSensor_t* sensor);
void _setBValue(volatile genericSensor_t* sensor);
void _clrBValue(volatile genericSensor_t* sensor);

uint8_t _getBStatus(volatile genericSensor_t* sensor);


#endif /* NUCLEOBUTTON_H_ */
