/*
 * MS5607.c
 *
 *  Created on: Mar 9, 2021
 *      Author: Jeff
 */

#include "MS5607.h"

genericSensor_t MS5607_init(SPI_HandleTypeDef *bus, GPIO_TypeDef *port, uint16_t pin) {
	/** Define MS5607 Struct **/
	MS5607_t _bmp = {0};
	genericSensor_t gBMP = {0};

	gBMP.sensorType = BMP_MS5607;
	gBMP.read = MS5607_read;
	gBMP.sensor.MS5607 = _bmp;
//#ifndef __NO_HAL_SPI
	gBMP.interface.SPI.bus = bus;
	gBMP.interface.SPI.port = port;
	gBMP.interface.SPI.pin = pin;
	gBMP.interface.SPI.timeout = HAL_MAX_DELAY;

//#endif
	gBMP.hasUpdate = true;
	gBMP.lock = false;



#ifndef __NO_HAL_SPI

	/** Define Local Variables **/
	MS5607_t* bmp = &(gBMP.sensor.MS5607);

	uint8_t dataIn[2]; // Buffer to load data received
	uint8_t cmd;       // Command sent to sensor
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);

	//Reset baro after power on
	cmd = 0x1E;
	if(sendSPI(&gBMP, &cmd, 1)) return gBMP;

	//Get value of C1
	cmd = 0xA1;
	if(receiveSPI(&gBMP, &cmd, 1, dataIn, 2)) return gBMP;
	bmp->senst1 = (dataIn[0] << 8) | dataIn[1];

	//Get value of C2
	cmd = 0xA2;
	if(receiveSPI(&gBMP, &cmd, 1, dataIn, 2)) return gBMP;
	bmp->offt1 = (dataIn[0] << 8) | dataIn[1];

	//Get value of C3
	cmd = 0xA3;
	if(receiveSPI(&gBMP, &cmd, 1, dataIn, 2)) return gBMP;
	bmp->tcs = (dataIn[0] << 8) | dataIn[1];

	//Get value of C4
	cmd = 0xA4;
	if(receiveSPI(&gBMP, &cmd, 1, dataIn, 2)) return gBMP;
	bmp->tco = (dataIn[0] << 8) | dataIn[1];

	//Get value of C5
	cmd = 0xA5;
	if(receiveSPI(&gBMP, &cmd, 1, dataIn, 2)) return gBMP;
	bmp->tref = (dataIn[0] << 8) | dataIn[1];

	//Get value of C6
	cmd = 0xA6;
	if(receiveSPI(&gBMP, &cmd, 1, dataIn, 2)) return gBMP;
	bmp->tempsens = (dataIn[0] << 8) | dataIn[1];

	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
#endif
	// Update with all values

	return gBMP;
}

uint8_t MS5607_read(genericSensor_t* sensor) {
	MS5607_t* bmp = &(sensor->sensor.MS5607);

	while(sensor->lock)
	#ifndef HARDWARE_EMULATOR
		retryTakeDelay(DEFAULT_TAKE_DELAY);
	#else
		break;
	#endif
	sensor->lock = true;

#ifndef __NO_HAL_SPI

	uint8_t dataIn[2]; // Buffer to load data received
	uint8_t cmd;       // Command sent to sensor
	SPI_t* SPI = &(sensor->interface.SPI);
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_RESET);


	//Get values from sensor
	cmd = D1_1024; //This value will define conversion time, accuracy, and current draw
	if (sendSPI(sensor, &cmd, 1)) return sensor->state;
	HAL_Delay(CONV_T_1024);

	cmd = 0x00;
	if (receiveSPI(sensor, &cmd, 1, dataIn, 2)) return sensor->state;
	bmp->digitalPres = (dataIn[0] << 8) | dataIn[1];

	cmd = D2_1024; //This value will define conversion time, accuracy, and current draw
	if (sendSPI(sensor, &cmd, 1)) return sensor->state;
	HAL_Delay(CONV_T_1024);

	cmd = 0x00;
	if (receiveSPI(sensor, &cmd, 1, dataIn, 2)) return sensor->state;
	bmp->digitalTemp = (dataIn[0] << 8) | dataIn[1];

	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_SET);
	//unlockSPI(sensor);
#endif

	//Calculate calibrated pressure
	//T = D2 - TREF = D2 - C5 * 2 ^ 8
	bmp->deltaT = bmp->digitalTemp - bmp->tref * 256;
	//TEMP = 20°C + dT* TEMPSENS = 2000 + dT * C6 / 2 ^ 23
	bmp->temp = 2000 + bmp->deltaT * bmp->tempsens / 8388608;
	//OFF = OFFT1 + TCO* dT = C2 * 2 ^ 17 + (C4 * dT) / 2 ^ 6
	bmp->off = bmp->offt1 * 131072 + (bmp->tco * bmp->deltaT) / 64;
	//SENS = SENST1 + TCS * dT = C1 * 2 ^ 16 + (C3 * dT) / 2 ^ 7
	bmp->sens = bmp->senst1 * 65536 + (bmp->tcs * bmp->deltaT) / 128;
	//P = D1 * SENS - OFF = (D1 * SENS / 2 ^ 21 - OFF) / 2 ^ 15
	bmp->pressure = (bmp->digitalPres * bmp->sens / 2097152 - bmp->off) / 32768; //This is the magic number in mbar

	return sensor->state;
}






