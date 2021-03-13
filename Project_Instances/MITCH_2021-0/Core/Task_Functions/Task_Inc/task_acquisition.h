/*
 * task_acquisition.h
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */

#ifndef TASK_FUNCTIONS_TASK_INC_TASK_ACQUISITION_H_
#define TASK_FUNCTIONS_TASK_INC_TASK_ACQUISITION_H_

#include "generic_interface.h"
#include "interface_structs.h"
#include "system_functions.h"

#include "MS5607.h"

volatile genericDevice_t gps;
volatile genericDevice_t bmp;
volatile genericDevice_t imu;
volatile genericDevice_t ala;

void task_acquisition_setup();
void task_acquisition_loop();

#endif /* TASK_FUNCTIONS_TASK_INC_TASK_ACQUISITION_H_ */
