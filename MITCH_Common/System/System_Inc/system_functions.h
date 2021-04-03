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

#define __HAL_OK_STR "HAL_OK"
#define __HAL_ERROR_STR "HAL_ERROR"
#define __HAL_BUSY_STR "HAL_BUSY"
#define __HAL_TIMEOUT_STR "HAL_TIMEOUT"

#define EVAL(EXP) (EXP ? 1 : 0)
#define INV(EXP) (typeof(EXP))(~EXP)

#define PRINT_BIN(EXP) ({for(int i = sizeof(EXP)*8-1; i >= 0; i--)\
							printf(EVAL(EXP & 1<<i)?"1":"0");})

#define PRINT_BIN_NL(EXP) ({for(int i = sizeof(EXP)*8-1; i >= 0; i--)\
							printf(EVAL(EXP &1<<i)?"1":"0");\
							printf("\r\n");})


/*
typedef enum {
	DENIED,
	APPROVED,
} AccessRequest_t;
*/
uint32_t getTimeStamp(void);
void retryTakeDelay(TickType_t length);

char* statusStr(HAL_StatusTypeDef status);

//AccessRequest_t access(bool* deviceLock, bool* structLock, TickType_t delay, uint8_t attempts);

#endif /* SYSTEM_SYSTEM_INC_SYSTEM_FUNCTIONS_H_ */
