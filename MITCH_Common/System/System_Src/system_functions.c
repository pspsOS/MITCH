/*
 * system_functions.c
 *
 *  Created on: Mar 8, 2021
 *      Author: Jeff
 */

#include "system_functions.h"

/**
 * @brief Get system timestamp
 * Gets the system timestamp. Returns 0 when run from testbed.
 *
 * @param None
 * @return None
 *
 * @author Jeff Kaji
 * @date 12/24/2020
 */
uint32_t getTimeStamp(void) {
	#ifdef HARDWARE_EMULATOR
		return 0;
	#else
		return HAL_GetTick();
	#endif
}

/**
 * @brief Quick delay for take retry
 * Creates a short rtos delay for take retry
 *
 * @param length: TBD
 * @retval None
 *
 * @author Jeff Kaji
 * @date 12/28/2020
 */
void retryTakeDelay(int length) {
#ifndef HARDWARE_EMULATOR
	vTaskDelay(length);
#endif
}
