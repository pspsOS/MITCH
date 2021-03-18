#include "generic_interface.h"

genericDevice_t MT3339_init(UART_HandleTypeDef *huart);
uint8_t MT3339_read(genericDevice_t* device);

