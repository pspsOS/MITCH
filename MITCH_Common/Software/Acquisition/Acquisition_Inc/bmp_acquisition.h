/*
 * bmp_acquisition.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Jeff
 */

#ifndef SOFTWARE_ACQUISITION_ACQUISITION_INC_BMP_ACQUISITION_H_
#define SOFTWARE_ACQUISITION_ACQUISITION_INC_BMP_ACQUISITION_H_

#include "bmp_acquisition.h"
#include "generic_interface.h"
#include "interface_structs.h"
#include "system_functions.h"

void bmpSetInterfaceLock(InterfaceLock_t* lock);
HAL_StatusTypeDef bmpRead(genericSensor_t* device);

#endif /* SOFTWARE_ACQUISITION_ACQUISITION_INC_BMP_ACQUISITION_H_ */
