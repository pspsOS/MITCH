/*
 * Nucleo_Profiles.c
 *
 *  Created on: Mar 27, 2021
 *      Author: Jeff
 */

#include "Nucleo_Profiles.h"


#ifdef NUCLEO_F4
void NucleoF4_Init() {

	#ifdef DO_RETARGET
	#include "retarget.h"
	extern UART_HandleTypeDef huart2;
	RetargetInit(&huart2);

#ifndef NO_CLEAR
	for(int i = 0; i < 500; i++) printf(" \r\n");
	HAL_Delay(250);
	printf("Starting:\r\n");
	HAL_Delay(250);
#endif
	#endif

	#ifndef NO_BUTTON
	btn = button_init(B1_GPIO_Port, B1_Pin);
	button_Invert(&btn);
	#endif

	#ifndef NO_LED
	LD2 = LED_init(LD2_GPIO_Port, LD2_Pin);
	#endif
}
#endif

#ifdef NUCLEO_L4
void NucleoL4_Init() {
#ifdef DO_RETARGET
	#include "retarget.h"
	extern UART_HandleTypeDef huart2;
	RetargetInit(&huart2);

#ifndef NO_CLEAR
	for(int i = 0; i < 500; i++) printf(" \r\n");
	HAL_Delay(250);
	printf("Starting:\r\n");
	HAL_Delay(250);
#endif
	#endif

	#ifndef NO_LED
	LD3 = LED_init(LD3_GPIO_Port, LD3_Pin);
	#endif
}
#endif
