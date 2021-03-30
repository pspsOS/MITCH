/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/** System Flags **/
#define DO_RETARGET

/** Task Rates **/
// Acquisition Rates Multiplier Settings
#define GPS_FREQ (1)        //   1 Hz
#define BMP_MULTIPLIER (10) //  10 Hz
#define IMU_MULTIPLIER (10) // 100 Hz

// Other Task Rates
#define PROCESSING_TASK_RATE    (125) // TODO: Determine optimal Processing Task Rate (currently 125 Hz)

// Task Delays are calculated from above rates (DO NOT EDIT)
#define ACQUISITION_TASK_RATE0  (GPS_FREQ)
#define ACQUISITION_TASK_RATE1  (GPS_FREQ * BMP_MULTIPLIER)
#define ACQUISITION_TASK_RATE2  (GPS_FREQ * BMP_MULTIPLIER * IMU_MULTIPLIER)
#define ACQUISITION_TASK_DELAY0  (1000 / ACQUISITION_TASK_RATE0 / portTICK_RATE_MS)
#define ACQUISITION_TASK_DELAY1  (1000 / ACQUISITION_TASK_RATE1 / portTICK_RATE_MS)
#define ACQUISITION_TASK_DELAY2  (1000 / ACQUISITION_TASK_RATE2 / portTICK_RATE_MS)

#define PROCESSING_TASK_DELAY    (1000 / PROCESSING_TASK_RATE / portTICK_RATE_MS)

#define DEFAULT_TAKE_DELAY (50)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
