/*
 * MS5607.c
 *
 *  Created on: Mar 9, 2021
 *      Author: Jeff
 */

#include "MS5607.h"

genericBMP_t MS5607_init(SPI_HandleTypeDef *bus, GPIO_TypeDef *port, uint16_t pin) {
	/** Define MS5607 Struct **/
	MS5607_t bmp;
	bmp.bus = bus;
	bmp.port = port;
	bmp.pin = pin;

	genericBMP_t gBMP;
	gBMP.bmpType = BMP_MS5607;
	gBMP.MS5607 = bmp;

	/** Define Local Variables **/
	uint8_t dataIn[2]; // Buffer to load data received
	uint8_t cmd;       // Command sent to device

#ifndef __NO_HAL_SPI
	//Reset baro after power on
	cmd = 0x1E;
	if(sendSPI(&cmd, 1, port, pin, bus, BMP_MS5607)) return gBMP;

	//Get value of C1
	cmd = 0xA1;
	if(receiveSPI(&cmd, 1, dataIn, 2, port, pin, bus, BMP_MS5607)) return gBMP;
	bmp.senst1 = (dataIn[0] << 8) | dataIn[1];

	//Get value of C2
	cmd = 0xA2;
	if(receiveSPI(&cmd, 1, dataIn, 2, port, pin, bus, BMP_MS5607)) return gBMP;
	bmp.offt1 = (dataIn[0] << 8) | dataIn[1];

	//Get value of C3
	cmd = 0xA3;
	if(receiveSPI(&cmd, 1, dataIn, 2, port, pin, bus, BMP_MS5607)) return gBMP;
	bmp.tcs = (dataIn[0] << 8) | dataIn[1];

	//Get value of C4
	cmd = 0xA4;
	if(receiveSPI(&cmd, 1, dataIn, 2, port, pin, bus, BMP_MS5607)) return gBMP;
	bmp.tco = (dataIn[0] << 8) | dataIn[1];

	//Get value of C5
	cmd = 0xA5;
	if(receiveSPI(&cmd, 1, dataIn, 2, port, pin, bus, BMP_MS5607)) return gBMP;
	bmp.tref = (dataIn[0] << 8) | dataIn[1];

	//Get value of C6
	cmd = 0xA6;
	if(receiveSPI(&cmd, 1, dataIn, 2, port, pin, bus, BMP_MS5607)) return gBMP;
	bmp.tempsens = (dataIn[0] << 8) | dataIn[1];

#endif
	// Update with all values
	gBMP.MS5607 = bmp;

	return gBMP;
}


