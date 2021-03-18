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


HAL_StatusTypeDef button_read(genericDevice_t* device);


uint8_t _setHSF(uint8_t status) {
	return status | _BUTTON_HSF_MASK;
}


uint8_t _clrHSF(uint8_t status) {
	return _setHSF(status) - _BUTTON_HSF_MASK;
}

uint8_t _setHRF(uint8_t status) {
	return status | _BUTTON_HRF_MASK;
}


uint8_t _clrHRF(uint8_t status) {
	return _setHSF(status) - _BUTTON_HRF_MASK;
}

uint8_t _setBMode(uint8_t status, ButtonMode_t mode) {
	switch(mode) {
	case ON_CHANGE:
		return ((uint8_t)-1 - _BUTTON_MODE_MASK) & status;
		break;
	case ON_VALUE:
		return (status | _BUTTON_MODE_MASK) - _BUTTON_MODE_MASK;
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
}
