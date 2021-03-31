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

volatile LED_t LED_init(GPIO_TypeDef* port, uint16_t pin);

GPIO_PinState LED_GetState(volatile LED_t* led);
void LED_SetState(volatile LED_t* led, GPIO_PinState state);
void LED_Set(volatile LED_t* led);
void LED_Reset(volatile LED_t* led);
void LED_Invert(volatile LED_t* led);

bool _getLINV(volatile LED_t* led);
void _setLINV(volatile LED_t* led);
void _clrLINV(volatile LED_t* led);

bool _getLState(volatile LED_t* led);
void _setLState(volatile LED_t* led);
void _clrLState(volatile LED_t* led);
#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_LED_H_ */
