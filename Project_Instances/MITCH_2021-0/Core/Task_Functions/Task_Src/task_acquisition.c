/*
 * task_acquisition.c
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */

#include "task_acquisition.h"

extern SPI_HandleTypeDef hspi1;

void task_acquisition_setup() {
	bmp = MS5607_init(&hspi1, CS_BMP_GPIO_Port, CS_BMP_Pin);
}





void task_acquisition_loop();
