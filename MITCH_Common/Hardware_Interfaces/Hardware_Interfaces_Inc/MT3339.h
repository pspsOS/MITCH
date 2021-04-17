#include "generic_interface.h"
#include "Adafruit_GPS.h"

genericSensor_t MT3339_init(UART_HandleTypeDef *huart);
uint8_t MT3339_read(volatile genericSensor_t* sensor);
HAL_StatusTypeDef MT3339_receive(volatile genericSensor_t* sensor);


