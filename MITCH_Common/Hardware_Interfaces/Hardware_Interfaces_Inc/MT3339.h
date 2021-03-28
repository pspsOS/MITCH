#include "generic_interface.h"

volatile genericSensor_t MT3339_init(UART_HandleTypeDef *huart);
uint8_t MT3339_read(volatile genericSensor_t* sensor);

