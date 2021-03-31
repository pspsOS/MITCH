#include "generic_interface.h"

genericSensor_t MT3339_init(UART_HandleTypeDef *huart);
uint8_t MT3339_read(volatile genericSensor_t* sensor);
HAL_StatusTypeDef MT3339_receive(genericSensor_t* sensor,uint8_t* buffer);
