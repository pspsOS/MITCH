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

	return (uint8_t) value;
}

ButtonState_t button_getState(genericDevice_t* device) {
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


// INV
bool _getINV(genericDevice_t* device) {
	return EVAL(device->device.button.status & _BUTTON_INV_MASK);
}
void _setINV(genericDevice_t* device) {
	device->device.button.status |= _BUTTON_INV_MASK;
}
void _clrINV(genericDevice_t* device) {
	device->device.button.status &= INV(_BUTTON_INV_MASK);
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

uint8_t _getBStatus(genericDevice_t* device) {
	return device->device.button.status;
}

