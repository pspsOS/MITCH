#include "Adafruit_GPS.h"

#include "MT3339.h"
#include <string.h>

genericSensor_t MT3339_init(UART_HandleTypeDef *huart) {
	/** Define MT3339 Struct **/
	MT3339_t _gps = {0};

	genericSensor_t gGPS = {0};
	gGPS.sensorType = GPS_MT3339;
	gGPS.read = MT3339_read;
	gGPS.sensor.MT3339 = _gps;
	gGPS.interface.UART.huart = huart;

#ifndef __NO_HAL_UART
	/** Define Local Variables **/
	//MT3339_t* gps = &(gGPS.sensor.MT3339);
	uint8_t temporary; // Buffer to load data received


	HAL_Delay(10);
	//printf("\nthe size is: %d\n",sizeof(trans));

	HAL_Delay(10);

	Adafruit_GPS(*huart);

	HAL_Delay(10);

	sendCommand(huart, PMTK_SET_BAUD_9600);
	HAL_Delay(10);
	sendCommand(huart, PMTK_SET_NMEA_OUTPUT_RMCGGA);
	HAL_Delay(10);
	//sendCommand(huart2, PMTK_SET_NMEA_UPDATE_10HZ);
	sendCommand(huart, PMTK_API_SET_FIX_CTL_5HZ);

	HAL_Delay(10);
	sendCommand(huart, PGCMD_ANTENNA);
	HAL_Delay(1000);
	HAL_UART_Receive_DMA(huart, &temporary, 1);
	//printf(PMTK_Q_RELEASE);
	//printf("Connection established at 9600 baud...\n");
	HAL_Delay(1);
#endif


	return gGPS;
}

uint8_t MT3339_read(genericSensor_t* sensor) {
	MT3339_t* gps = &(sensor->sensor.MT3339);

	 if ( !parse(lastNMEA()) ) {
		 return (uint8_t) sensor->state;
	 }
	 strncpy(gps->gpsString,lastNMEA(),MAX_NMEA);


	return (uint8_t) sensor->state;

}


HAL_StatusTypeDef MT3339_receive(genericSensor_t* sensor,uint8_t* buffer, char* target) {
#ifndef __NO_HAL_UART
	MT3339_t* gps = &(sensor->sensor.MT3339);
	UART_HandleTypeDef* huart = sensor->interface.UART.huart;
	 // Buffer to load data received
	//if (huart->Instance == sensor->interface.UART.huart->Instance)  {
//			printf("hi");
			read(*buffer);
			if (newNMEAreceived()) {

				if ( parse(lastNMEA()) ) {
					strncpy(target,lastNMEA(),MAX_NMEA);
					sensor->sensor.MT3339.buffer = '@';
//					strncpy(sensor->sensor.MT3339.gpsString,lastNMEA(),MAX_NMEA);
//					printf("^%s\r\n",sensor->sensor.MT3339.gpsString);
					printf("Innie:%c\r\n",sensor->sensor.MT3339.buffer);
				}
			}
	//}
#endif
	return sensor->state;
}
