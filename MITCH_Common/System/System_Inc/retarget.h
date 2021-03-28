// All credit to Carmine Noviello for this code
// https://github.com/cnoviello/mastering-stm32/blob/master/nucleo-f030R8/system/include/retarget/retarget.h

#ifndef _RETARGET_H__
#define _RETARGET_H__
#include "main.h"

#ifdef STM32F4
#include "Nucleo_Profiles.h"
#include "stm32f4xx_hal.h"
#endif

#ifdef STM32L4
#include "Nucleo_Profiles.h"
#include "stm32l4xx_hal.h"
#endif

#ifdef DO_RETARGET

#include <sys/stat.h>

void RetargetInit(UART_HandleTypeDef *huart);
int _isatty(int fd);
int _write(int fd, char* ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char* ptr, int len);
int _fstat(int fd, struct stat* st);

#endif

#endif //#ifndef _RETARGET_H__
