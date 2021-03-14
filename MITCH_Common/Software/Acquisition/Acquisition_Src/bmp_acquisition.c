/*
 * bmp_acquisition.c
 *
 *  Created on: Mar 11, 2021
 *      Author: Jeff
 */

#include "bmp_acquisition.h"

InterfaceLock_t* _lock = 0;

void bmpSetInterfaceLock(InterfaceLock_t* lock) {
	_lock = lock;
}

HAL_StatusTypeDef bmpRead(genericDevice_t* device) {

	//if(_lock) interfaceLock(_lock, DEFAULT_TAKE_DELAY, device->interface.SPI.timeout);
	device->read(device);
	if(_lock) interfaceUnlock(_lock, device);
	return device->state;
}
