/*
 * Nucleo_Profiles.h
 *
 *  Created on: Mar 27, 2021
 *      Author: Jeff
 */

#ifndef SYSTEM_SYSTEM_INC_NUCLEO_PROFILES_H_
#define SYSTEM_SYSTEM_INC_NUCLEO_PROFILES_H_

#include "main.h"

#ifdef NUCLEO_F4

#include "stm32f411xe.h"

#if !defined(NO_RETARGET) && !defined(DO_RETARGET)
#define DO_RETARGET
#endif

#ifndef NO_BUTTON
	#include "button.h"
	#ifndef B1_Pin
	#define B1_Pin GPIO_PIN_13
	#endif
	#ifndef B1_GPIO_Port
	#define B1_GPIO_Port GPIOC
	#endif
	volatile genericSensor_t btn;
#endif /* NO_BUTTON */

#ifndef NO_LED
#include "led.h"
	#ifndef LD2_Pin
	#define LD2_Pin GPIO_PIN_5
	#endif
	#ifndef LD2_GPIO_Port
	#define LD2_GPIO_Port GPIOA
	#endif
	volatile LED_t LD2;
#endif /* NO_LED */

void NucleoF4_Init();

#endif /* NUCLEO_F4 */

#endif /* SYSTEM_SYSTEM_INC_NUCLEO_PROFILES_H_ */
