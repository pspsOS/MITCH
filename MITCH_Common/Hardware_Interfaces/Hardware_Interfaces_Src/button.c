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
		if(_getBINV(sensor)) value = !value;
	#endif

	// Handle Change Flag
	if(value != prevValue) _setBChange(sensor);
	else _clrBChange(sensor);

	// Handle Value Flag;
	if(value) _setBValue(sensor);
	else _clrBValue(sensor);


	if((value != prevValue) && value) _doRToggle(sensor);
	if((value != prevValue) && !value) _doFToggle(sensor);
	return (uint8_t) value;
}

ButtonState_t button_GetState(genericSensor_t* sensor) {
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

bool button_OnSet(genericSensor_t* sensor) {
	return _getBValue(sensor);
}
bool button_OnReset(genericSensor_t* sensor) {
	return !_getBValue(sensor);
}
bool button_OnRising(genericSensor_t* sensor) {
	return _getBValue(sensor) && _getBChange(sensor);
}
bool button_OnFalling(genericSensor_t* sensor) {
	return !_getBValue(sensor) && _getBChange(sensor);
}
bool button_OnRToggle(genericSensor_t* sensor) {
	return button_OnRising(sensor) && _getRToggle(sensor);
}
bool button_OnFToggle(genericSensor_t* sensor) {
	return button_OnFalling(sensor) && _getFToggle(sensor);
}


// INV
bool _getBINV(genericSensor_t* sensor) {
	return EVAL(sensor->sensor.button.status & _BUTTON_INV_MASK);
}
void _setBINV(genericSensor_t* sensor) {
	sensor->sensor.button.status |= _BUTTON_INV_MASK;
}
void _clrBINV(genericSensor_t* sensor) {
	sensor->sensor.button.status &= INV(_BUTTON_INV_MASK);
}


// Button Rising Toggle
bool _getRToggle(genericSensor_t* sensor) {
	return EVAL(sensor->sensor.button.status & _BUTTON_RTOGGLE_MASK);
}
void _setRToggle(genericSensor_t* sensor) {
	sensor->sensor.button.status |= _BUTTON_RTOGGLE_MASK;
}
void _clrRToggle(genericSensor_t* sensor) {
	sensor->sensor.button.status &= INV(_BUTTON_RTOGGLE_MASK);
}
void _doRToggle(genericSensor_t* sensor) {
	(_getRToggle(sensor)) ? (_clrRToggle(sensor)) : (_setRToggle(sensor));
}


// Button Falling Toggle
bool _getFToggle(genericSensor_t* sensor) {
	return EVAL(sensor->sensor.button.status & _BUTTON_FTOGGLE_MASK);
}
void _setFToggle(genericSensor_t* sensor) {
	sensor->sensor.button.status |= _BUTTON_FTOGGLE_MASK;
}

void _clrFToggle(genericSensor_t* sensor) {
	sensor->sensor.button.status &= INV(_BUTTON_FTOGGLE_MASK);
}
void _doFToggle(genericSensor_t* sensor) {
	(_getFToggle(sensor)) ? (_clrFToggle(sensor)) : (_setFToggle(sensor));
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

