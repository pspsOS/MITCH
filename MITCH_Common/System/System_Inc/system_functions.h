/*
 * system_functions.h
 *
 *  Created on: Mar 8, 2021
 *      Author: Jeff
 */

#ifndef SYSTEM_SYSTEM_INC_SYSTEM_FUNCTIONS_H_
#define SYSTEM_SYSTEM_INC_SYSTEM_FUNCTIONS_H_

#include "STM.h"
#include <stdint.h>
#include <stdbool.h>

#define GET_BIT(p,n) (((p >> n) & 1) == 1)


typedef enum {
	DENIED,
	APPROVED,
} AccessRequest_t;

uint32_t getTimeStamp(void);
void retryTakeDelay(TickType_t length);

AccessRequest_t access(bool* deviceLock, bool* structLock, TickType_t delay, uint8_t attempts);

#endif /* SYSTEM_SYSTEM_INC_SYSTEM_FUNCTIONS_H_ */
