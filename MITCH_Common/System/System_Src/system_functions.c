/*
 * system_functions.c
 *
 *  Created on: Mar 8, 2021
 *      Author: Jeff
 */

#include "system_functions.h"
#include "main.h"

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
void retryTakeDelay(TickType_t length) {
#ifdef INC_TASK_H
	vTaskDelay(length);
#endif
}


char* statusStr(HAL_StatusTypeDef status) {
	switch(status) {
	case HAL_OK:
		return &__HAL_OK_STR[0];
		break;
	case HAL_ERROR:
		return &__HAL_ERROR_STR[0];
		break;
	case HAL_BUSY:
		return &__HAL_BUSY_STR[0];
		break;
	case HAL_TIMEOUT:
		return &__HAL_TIMEOUT_STR[0];
		break;
	}
	return NULL;
}

/*
AccessRequest_t access(bool* deviceLock, bool* structLock, TickType_t delay, uint8_t attempts) {
	AccessRequest_t result = DENIED;
#ifndef HARDWARE_EMULATOR
	for(uint8_t i = 0; i < attempts; i++) {
		if(!(*deviceLock) && !(*structLock)) {
			*deviceLock = true;
			*structLock = true;
			result = APPROVED;
			break;
		}
		vTaskDelay(delay);
	}
#else
	// TODO: Implement access hardware emulation
#endif
	return result;
}
*/
