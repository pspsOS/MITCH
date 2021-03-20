/*
 * button.c
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#include "button.h"

genericSensor_t button_init(GPIO_TypeDef *port, uint16_t pin) {
	button_t _btn = {0};
	genericSensor_t gBTN = {0};

	gBTN.sensorType = GPIO_BUTTON;
	gBTN.read = button_read;

	gBTN.sensor.button = _btn;

	gBTN.interface.PIN.port = port;
	gBTN.interface.PIN.pin = pin;

	//#ifndef HARDWARE_EMULATOR
	gBTN.state = HAL_OK;
	//#endif

	gBTN.hasUpdate = false;
	gBTN.lock = false;

	return gBTN;
}


uint8_t button_read(genericSensor_t* sensor) {
	bool prevValue = _getBValue(sensor);
	bool value = prevValue;

	#ifndef HARDWARE_EMULATOR
		PIN_t pin = sensor->interface.PIN;
		value = HAL_GPIO_ReadPin(pin.port, pin.pin);
		if(_getINV(sensor)) value = !value;
	#endif

	// Handle Change Flag
	if(value != prevValue) _setBChange(sensor);
	else _clrBChange(sensor);

	// Handle Value Flag;
	if(value) _setBValue(sensor);
	else _clrBValue(sensor);

	return (uint8_t) value;
}

ButtonState_t button_getState(genericSensor_t* sensor) {
	button_t* btn = &(sensor->sensor.button);
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
bool _getINV(genericSensor_t* sensor) {
	return EVAL(sensor->sensor.button.status & _BUTTON_INV_MASK);
}
void _setINV(genericSensor_t* sensor) {
	sensor->sensor.button.status |= _BUTTON_INV_MASK;
}
void _clrINV(genericSensor_t* sensor) {
	sensor->sensor.button.status &= INV(_BUTTON_INV_MASK);
}


// Button Change
bool _getBChange(genericSensor_t* sensor) {
	return EVAL(sensor->sensor.button.status & _BUTTON_CHANGE_MASK);
}
void _setBChange(genericSensor_t* sensor) {
	sensor->sensor.button.status |= _BUTTON_CHANGE_MASK;
}

void _clrBChange(genericSensor_t* sensor) {
	sensor->sensor.button.status &= INV(_BUTTON_CHANGE_MASK);
}

// Button Value
bool _getBValue(genericSensor_t* sensor) {
	return EVAL(sensor->sensor.button.status & _BUTTON_VALUE_MASK);
}
void _setBValue(genericSensor_t* sensor) {
	sensor->sensor.button.status |= _BUTTON_VALUE_MASK;
}

void _clrBValue(genericSensor_t* sensor) {
	sensor->sensor.button.status &= INV(_BUTTON_VALUE_MASK);
}

uint8_t _getBStatus(genericSensor_t* sensor) {
	return sensor->sensor.button.status;
}

