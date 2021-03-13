/*
 * STM.h
 *
 *  Created on: Mar 12, 2021
 *      Author: Jeff
 */

#ifndef SYSTEM_SYSTEM_INC_STM_H_
#define SYSTEM_SYSTEM_INC_STM_H_

#ifndef HARDWARE_EMULATOR
#include "cmsis_os.h"
#include "main.h"
#endif


/** Checks/Sets NO_STM_DEF Flag **/
#if !defined(__STM32F4xx_H)
	#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
	#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
	#define READ_BIT(REG, BIT)    ((REG) & (BIT))
	#define CLEAR_REG(REG)        ((REG) = (0x0))
	#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
	#define READ_REG(REG)         ((REG))
	#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
	#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

	#define __NO_STM_DEF
#endif
/** Checks/Sets NO_STM_DEV Flag **/
#if !defined(__STM32F411xE_H)
	typedef void GPIO_TypeDef;
	typedef enum {
	  GPIO_PIN_RESET = 0,
	  GPIO_PIN_SET
	}GPIO_PinState;
	#define __NO_STM_DEV
#endif

/** Checks/Sets NO_HAL_DEF Flag **/
#if !defined(__STM32F4xx_HAL_DEF)
	typedef enum {
	  HAL_OK       = 0x00U,
	  HAL_ERROR    = 0x01U,
	  HAL_BUSY     = 0x02U,
	  HAL_TIMEOUT  = 0x03U
	} HAL_StatusTypeDef;
	#define HAL_MAX_DELAY      0xFFFFFFFFU
	#define __NO_HAL_DEF
#endif

/** Checks/Sets NO_HAL_SPI Flag **/
#if !defined (STM32F4xx_HAL_SPI_H)
	typedef void SPI_HandleTypeDef;
	#define __NO_HAL_SPI
#endif

#endif /* SYSTEM_SYSTEM_INC_STM_H_ */
