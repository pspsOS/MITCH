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
	gBTN.device.button.rising_fun = __no_fun;
	gBTN.device.button.falling_fun = __no_fun;

	gBTN.interface.PIN.port = port;
	gBTN.interface.PIN.pin = pin;

	//#ifndef HARDWARE_EMULATOR
	gBTN.state = HAL_OK;
	//#endif

	gBTN.hasUpdate = false;
	gBTN.lock = false;

	return gBTN;
}


uint8_t n_read(genericDevice_t* device) {
	bool prevValue = _getBValue(device);
	bool value = prevValue;

	#ifndef HARDWARE_EMULATOR
		PIN_t pin = device->interface.PIN;
		value = HAL_GPIO_ReadPin(pin.port, pin.pin);
		if(_getINV(device)) value = !value;
	#endif

	// Handle Change Flag
	if(value != prevValue) _setBChange(device);
	else _clrBChange(device);

	// Handle Value Flag;
	if(value) _setBValue(device);
	else _clrBValue(device);

	return value;
}

ButtonState_t _getBState(genericDevice_t* device) {
	button_t* btn = &(device->device.button);
	switch(btn->status & _BUTTON_STATE_MASK) {
	case 0b00:
		return BUTTON_RESET;
		break;
	case 0b01:
		return BUTTON_SET;
		break;
	case 0b11:
		return BUTTON_RISING;
		break;
	case 0b10:
		return BUTTON_FALLING;
		break;
	default:
		return -1;
	}
}

uint8_t button_read(genericDevice_t* device) {
	button_t* btn = &(device->device.button);
	GPIO_PinState state = GPIO_PIN_RESET;

	bool do_fun = false;

	#ifndef HARDWARE_EMULATOR
	PIN_t pin = device->interface.PIN;
	state = HAL_GPIO_ReadPin(pin.port, pin.pin);
	#endif

	if(_getINV(device)) state = !state;

	switch(btn->status & _BUTTON_MODE_MASK) {
	case _BUTTON_MODE_CHANGE:
		if(state != (btn->status & _BUTTON_VALUE_MASK))
			do_fun = true;
		break;
	case _BUTTON_MODE_VALUE:
		do_fun = true;
		break;
	default:
		break;
	}
	//PRINT_BIN_NL(btn->status & _BUTTON_MODE_MASK);

	(state)?(_setBValue(device)):(_clrBValue(device));

	if(do_fun) switch(state) {
	case GPIO_PIN_RESET:
		if(_getHRF(device)) btn->reset_fun();
		break;
	case GPIO_PIN_SET:
		if(_getHSF(device)) btn->set_fun();
		break;
	default:
		break;
	}

	return state;
}

// INV
uint8_t _getINV(genericDevice_t* device) {
	return EVAL(device->device.button.status & _BUTTON_INV_MASK);
}
void _setINV(genericDevice_t* device) {
	device->device.button.status |= _BUTTON_INV_MASK;
}
void _clrINV(genericDevice_t* device) {
	device->device.button.status &= INV(_BUTTON_INV_MASK);
}

// HSF
uint8_t _getHSF(genericDevice_t* device) {
	return EVAL(device->device.button.status & _BUTTON_HSF_MASK);
}
void _setHSF(genericDevice_t* device) {
	device->device.button.status |= _BUTTON_HSF_MASK;
}
void _clrHSF(genericDevice_t* device) {
	device->device.button.status &= INV(_BUTTON_HSF_MASK);
}

// HRF
uint8_t _getHRF(genericDevice_t* device) {
	return EVAL(device->device.button.status & _BUTTON_HRF_MASK);
}
void _setHRF(genericDevice_t* device) {
	device->device.button.status |= _BUTTON_HRF_MASK;
}
void _clrHRF(genericDevice_t* device) {
	device->device.button.status &= INV(_BUTTON_HRF_MASK);
}

// Button Change
bool _getBChange(genericDevice_t* device) {
	return EVAL(device->device.button.status & _BUTTON_CHANGE_MASK);
}
void _setBChange(genericDevice_t* device) {
	device->device.button.status |= _BUTTON_CHANGE_MASK;
}

void _clrBChange(genericDevice_t* device) {
	device->device.button.status &= INV(_BUTTON_CHANGE_MASK);
}

// Button Value
bool _getBValue(genericDevice_t* device) {
	return EVAL(device->device.button.status & _BUTTON_VALUE_MASK);
}
void _setBValue(genericDevice_t* device) {
	device->device.button.status |= _BUTTON_VALUE_MASK;
}

void _clrBValue(genericDevice_t* device) {
	device->device.button.status &= INV(_BUTTON_VALUE_MASK);
}


// Button Mode
uint8_t _getBMode(genericDevice_t* device) {
	return EVAL(device->device.button.status & _BUTTON_MODE_MASK);
}

void _setBMode(genericDevice_t* device, ButtonMode_t mode) {
	switch(mode) {
	case ON_CHANGE:
		device->device.button.status &= INV(_BUTTON_MODE_MASK);
		device->device.button.status |= _BUTTON_MODE_CHANGE;
		break;
	case ON_VALUE:
		device->device.button.status &= INV(_BUTTON_MODE_MASK);
		device->device.button.status |= _BUTTON_MODE_VALUE;
		break;
	default:
		device->state = HAL_ERROR;
		break;
	}
}


button_fun _getBSF(genericDevice_t* device) {
	return device->device.button.set_fun;
}
void _setBSF(genericDevice_t* device, button_fun set_fun) {
	device->device.button.set_fun = set_fun;
	_setHSF(device);
}
void _clrBSF(genericDevice_t* device) {
	_clrHSF(device);
	device->device.button.set_fun = __no_fun;
}
button_fun _getBRF(genericDevice_t* device) {
	return device->device.button.reset_fun;
}
void _setBRF(genericDevice_t* device, button_fun reset_fun) {
	device->device.button.reset_fun = reset_fun;
	_setHSF(device);
}
void _clrBRF(genericDevice_t* device) {
	_clrHSF(device);
	device->device.button.reset_fun = __no_fun;
}

void __no_fun() {};

