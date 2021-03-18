#include "Adafruit_GPS.h"

#include "MT3339.h"
#include <string.h>

genericDevice_t MT3339_init(UART_HandleTypeDef *huart) {
	/** Define MT3339 Struct **/
	MT3339_t _gps = {0};

	genericDevice_t gGPS = {0};
	gGPS.deviceType = GPS_MT3339;
	gGPS.read = MT3339_read;
	gGPS.device.MT3339 = _gps;
	gGPS.interface.UART.huart = huart;

#ifndef __NO_HAL_UART
	/** Define Local Variables **/
	//MT3339_t* gps = &(gGPS.device.MT3339);
	uint8_t temporary; // Buffer to load data received


	HAL_Delay(10);
	//printf("\nthe size is: %d\n",sizeof(trans));
	HAL_UART_Receive_IT(huart, &temporary, 1);
	HAL_Delay(10);

	Adafruit_GPS(*huart);

	HAL_Delay(10);

	sendCommand(*huart, PMTK_SET_BAUD_9600);
	HAL_Delay(10);
	sendCommand(*huart, PMTK_SET_NMEA_OUTPUT_RMCGGA);
	HAL_Delay(10);
	//sendCommand(huart2, PMTK_SET_NMEA_UPDATE_10HZ);
	sendCommand(*huart, PMTK_API_SET_FIX_CTL_5HZ);

	HAL_Delay(10);
	sendCommand(*huart, PGCMD_ANTENNA);
	HAL_Delay(10);

	//printf(PMTK_Q_RELEASE);
	//printf("Connection established at 9600 baud...\n");
	HAL_Delay(1);
#endif


	return gGPS;
}

uint8_t MT3339_read(genericDevice_t* device) {
	MT3339_t* gps = &(device->device.MT3339);

	 if ( !parse(lastNMEA()) ) {
		 return (uint8_t) device->state;
	 }
	 strncpy(gps->gpsString,lastNMEA(),MAX_NMEA);


	return (uint8_t) device->state;

}


HAL_StatusTypeDef MT3339_receive(genericDevice_t* device,uint8_t* buffer) {
#ifndef __NO_HAL_UART
	MT3339_t* gps = &(device->device.MT3339);
	UART_HandleTypeDef* huart = device->interface.UART.huart;
	 // Buffer to load data received
	if (huart->Instance == device->interface.UART.huart->Instance)  {
			//printf("hi");
			HAL_UART_Receive_IT(huart,buffer, 1);
			read(*buffer);
	}
#endif
	return device->state;
}
