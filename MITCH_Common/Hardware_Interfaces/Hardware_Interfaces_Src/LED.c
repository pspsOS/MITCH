/*
 * LED.c
 *
 *  Created on: Mar 20, 2021
 *      Author: Jeff
 */


#include "led.h"

LED_t LED_init(GPIO_TypeDef* port, uint16_t pin) {
	LED_t led = {0};
	led.PIN.port = port;
	led.PIN.pin = pin;

	return led;
}

GPIO_PinState LED_GetState(LED_t* led) {
	return _getLState(led);
}
void LED_SetState(LED_t* led, GPIO_PinState state) {
	switch(state) {
	case GPIO_PIN_RESET:
		_clrLState(led);
		break;
	case GPIO_PIN_SET:
		_setLState(led);
	}

	#ifndef HARDWARE_EMULATOR
		if(_getLINV(led)) state = !state;
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, state);
	#endif
}

void LED_Set(LED_t* led) {
	_setLState(led);

#ifndef HARDWARE_EMULATOR
	if(_getLINV(led))
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_SET);
#endif
}

void LED_Reset(LED_t* led) {
	_clrLState(led);

#ifndef HARDWARE_EMULATOR
	if(_getLINV(led))
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_RESET);
#endif
}

bool _getLINV(LED_t* led) {
	return EVAL(led->status & _LED_INV_MASK);
}
void _setLINV(LED_t* led) {
	_getLState(led) ? _clrLState(led) : _setLState(led);
	led->status |= _LED_INV_MASK;
}
void _clrLINV(LED_t* led) {
	_getLState(led) ? _clrLState(led) : _setLState(led);
	led->status &= INV(_LED_INV_MASK);
}

bool _getLState(LED_t* led) {
	return EVAL(led->status & _LED_STATE_MASK);
}
void _setLState(LED_t* led) {
	led->status |= _LED_STATE_MASK;
}
void _clrLState(LED_t* led) {
	led->status &= INV(_LED_STATE_MASK);
}
