/*
 * led.h
 *
 *  Created on: Mar 20, 2021
 *      Author: Jeff
 */

#ifndef HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_LED_H_
#define HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_LED_H_

#include "generic_interface.h"

#define _LED_INV_MASK 	(uint8_t)(0b00000010)
#define _LED_STATE_MASK (uint8_t)(0b00000001)

LED_t LED_init(GPIO_TypeDef* port, uint16_t pin);

GPIO_PinState LED_GetState(LED_t* led);
void LED_SetState(LED_t* led, GPIO_PinState state);
void LED_Set(LED_t* led);
void LED_Reset(LED_t* led);
void LED_Invert(LED_t* led);

bool _getLINV(LED_t* led);
void _setLINV(LED_t* led);
void _clrLINV(LED_t* led);

bool _getLState(LED_t* led);
void _setLState(LED_t* led);
void _clrLState(LED_t* led);
#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_LED_H_ */
