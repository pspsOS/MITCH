#include "generic_interface.h"

genericSensor_t MT3339_init(UART_HandleTypeDef *huart);
uint8_t MT3339_read(genericSensor_t* sensor);

