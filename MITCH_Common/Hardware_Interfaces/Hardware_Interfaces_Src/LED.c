/*
 * LED.c
 *
 *  Created on: Mar 20, 2021
 *      Author: Jeff
 */


#include "led.h"

volatile LED_t LED_init(GPIO_TypeDef* port, uint16_t pin) {
	LED_t led = {0};
	led.PIN.port = port;
	led.PIN.pin = pin;

	return led;
}

GPIO_PinState LED_GetState(volatile LED_t* led) {
	return _getLState(led);
}
void LED_SetState(volatile LED_t* led, GPIO_PinState state) {
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

void LED_Set(volatile LED_t* led) {
	_setLState(led);

#ifndef HARDWARE_EMULATOR
	if(_getLINV(led))
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_SET);
#endif
}

void LED_Reset(volatile LED_t* led) {
	_clrLState(led);

#ifndef HARDWARE_EMULATOR
	if(_getLINV(led))
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(led->PIN.port, led->PIN.pin, GPIO_PIN_RESET);
#endif
}

void LED_Invert(volatile LED_t* led) {
	_getLINV(led) ? _clrLINV(led) : _setLINV(led);
}

bool _getLINV(volatile LED_t* led) {
	return EVAL(led->status & _LED_INV_MASK);
}
void _setLINV(volatile LED_t* led) {
	_getLState(led) ? _clrLState(led) : _setLState(led);
	led->status |= _LED_INV_MASK;
}
void _clrLINV(volatile LED_t* led) {
	_getLState(led) ? _clrLState(led) : _setLState(led);
	led->status &= INV(_LED_INV_MASK);
}

bool _getLState(volatile LED_t* led) {
	return EVAL(led->status & _LED_STATE_MASK);
}
void _setLState(volatile LED_t* led) {
	led->status |= _LED_STATE_MASK;
}
void _clrLState(volatile LED_t* led) {
	led->status &= INV(_LED_STATE_MASK);
}
