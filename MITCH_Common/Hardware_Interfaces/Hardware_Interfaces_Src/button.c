/*
 * button.c
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#include "button.h"

genericDevice_t button_init(GPIO_TypeDef *port, uint16_t pin) {
	button_t _btn = {0};
	genericDevice_t gBTN = {0};

	gBTN.deviceType = GPIO_BUTTON;
	gBTN.read = button_read;

	gBTN.device.button = _btn;
	gBTN.device.button.set_fun = __no_fun;
	gBTN.device.button.reset_fun = __no_fun;

	gBTN.interface.PIN.port = port;
	gBTN.interface.PIN.pin = pin;

	//#ifndef HARDWARE_EMULATOR
	gBTN.state = HAL_OK;
	//#endif

	gBTN.hasUpdate = false;
	gBTN.lock = false;

	return gBTN;
}


uint8_t button_read(genericDevice_t* device) {
	button_t* btn = &(device->device.button);
	GPIO_PinState state = GPIO_PIN_RESET;

	bool do_fun = false;

	#ifndef HARDWARE_EMULATOR
	PIN_t pin = device->interface.PIN;
	state = HAL_GPIO_ReadPin(pin.port, pin.pin);
	#endif

	if(_getINV(btn->status)) state = !state;

	switch(btn->status & _BUTTON_MODE_MASK) {
	case _BUTTON_MODE_CHANGE:
		if(state != (btn->status & _BUTTON_STATE_MASK))
			do_fun = true;
		break;
	case _BUTTON_MODE_VALUE:
		do_fun = true;
		break;
	default:
		break;
	}
	//PRINT_BIN_NL(btn->status & _BUTTON_MODE_MASK);

	btn->status = (state)?(_setBState(btn->status)):(_clrBState(btn->status));

	if(do_fun) switch(state) {
	case GPIO_PIN_RESET:
		btn->reset_fun();
		break;
	case GPIO_PIN_SET:
		btn->set_fun();
		break;
	default:
		break;
	}

	return state;
}

// INV
uint8_t _getINV(uint8_t status) {
	return EVAL(status & _BUTTON_INV_MASK);
}
uint8_t _setINV(uint8_t status) {
	return status | _BUTTON_INV_MASK;
}
uint8_t _clrINV(uint8_t status) {
	return _setINV(status) - _BUTTON_INV_MASK;
}

// HSF
uint8_t _getHSF(uint8_t status) {
	return EVAL(status & _BUTTON_HSF_MASK);
}
uint8_t _setHSF(uint8_t status) {
	return status | _BUTTON_HSF_MASK;
}
uint8_t _clrHSF(uint8_t status) {
	return _setHSF(status) - _BUTTON_HSF_MASK;
}

// HRF
uint8_t _getHRF(uint8_t status) {
	return EVAL(status & _BUTTON_HRF_MASK);
}
uint8_t _setHRF(uint8_t status) {
	return status | _BUTTON_HRF_MASK;
}
uint8_t _clrHRF(uint8_t status) {
	return _setHSF(status) - _BUTTON_HRF_MASK;
}

// Button Mode
uint8_t _getBMode(uint8_t status) {
	return EVAL(status & _BUTTON_MODE_MASK);
}

uint8_t _setBMode(uint8_t status, ButtonMode_t mode) {
	switch(mode) {
	case ON_CHANGE:
		return (status | _BUTTON_MODE_MASK) - _BUTTON_MODE_MASK;
		break;
	case ON_VALUE:
		return status | _BUTTON_MODE_MASK;
		break;
	default:
		return status;
	}
}

uint8_t _setBState(uint8_t status) {
	return status | _BUTTON_STATE_MASK;
}

uint8_t _clrBState(uint8_t status) {
	return _setBState(status) - _BUTTON_STATE_MASK;
}

void __no_fun() {};

/*
uint8_t _setBStateVal(uint8_t status, GPIO_PinState state) {
	switch(state) {
	case GPIO_PIN_SET:
		return _setBState(status);
		break;
	case GPIO_PIN_RESET:
		return _clrBState(status);
		break;
	default:
		return status;
	}
}*/
