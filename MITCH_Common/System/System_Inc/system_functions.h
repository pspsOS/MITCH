/*
 * system_functions.h
 *
 *  Created on: Mar 8, 2021
 *      Author: Jeff
 */

#ifndef SYSTEM_SYSTEM_INC_SYSTEM_FUNCTIONS_H_
#define SYSTEM_SYSTEM_INC_SYSTEM_FUNCTIONS_H_

#ifndef HARDWARE_EMULATOR
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#endif

uint32_t getTimeStamp(void);
void retryTakeDelay(int length);

#endif /* SYSTEM_SYSTEM_INC_SYSTEM_FUNCTIONS_H_ */
