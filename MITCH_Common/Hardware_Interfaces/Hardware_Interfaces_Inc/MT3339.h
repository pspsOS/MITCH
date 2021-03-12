#include "generic_interface.h"

genericDevice_t MT3339_init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef MT3339_read(genericDevice_t* device);

