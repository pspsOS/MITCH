/*
 * MS5607.c
 *
 *  Created on: Mar 9, 2021
 *      Author: Jeff
 */

#include "MS5607.h"

genericDevice_t MS5607_init(SPI_HandleTypeDef *bus, GPIO_TypeDef *port, uint16_t pin) {
	/** Define MS5607 Struct **/
	MS5607_t _bmp = {0};

	genericDevice_t gBMP = {0};
	gBMP.deviceType = BMP_MS5607;
	gBMP.read = MS5607_read;
	gBMP.device.MS5607 = _bmp;
	gBMP.interface.SPI.bus = bus;
	gBMP.interface.SPI.port = port;
	gBMP.interface.SPI.pin = pin;

	/** Define Local Variables **/
	MS5607_t* bmp = &(gBMP.device.MS5607);
	uint8_t dataIn[2]; // Buffer to load data received
	uint8_t cmd;       // Command sent to device
	bmp->interface = &(gBMP.interface);
	bmp->interface->SPI.bus = bus;



#ifndef __NO_HAL_SPI
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

#endif
	// Update with all values

	return gBMP;
}

HAL_StatusTypeDef MS5607_read(genericDevice_t* device) {
	MS5607_t* bmp = &(device->device.MS5607);

	uint8_t dataIn[2]; // Buffer to load data received
	uint8_t cmd;       // Command sent to device

	//Get values from sensor
	cmd = D1_1024; //This value will define conversion time, accuracy, and current draw
	if (sendSPI(device, &cmd, 1)) return device->state;
	HAL_Delay(CONV_T_1024);

	cmd = 0x00;
	if (receiveSPI(device, &cmd, 1, dataIn, 2)) return device->state;
	bmp->digitalPres = (dataIn[0] << 8) | dataIn[1];

	cmd = D2_1024; //This value will define conversion time, accuracy, and current draw
	if (sendSPI(device, &cmd, 1)) return device->state;
	HAL_Delay(CONV_T_1024);

	cmd = 0x00;
	if (receiveSPI(device, &cmd, 1, dataIn, 2)) return device->state;
	bmp->digitalTemp = (dataIn[0] << 8) | dataIn[1];

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

	return device->state;
}

/*
HAL_StatusTypeDef MS5607_send(MS5607_t* bmp, uint8_t* cmd, int cmdlen) {
	bmp->state = sendSPI(cmd,cmdlen,bmp->port,bmp->pin,bmp->bus,BMP_MS5607);
	return bmp->state;
}


HAL_StatusTypeDef MS5607_receive(MS5607_t* bmp, uint8_t* cmd, int cmdlen, uint8_t* data, int datalen) {
	bmp->state = receiveSPI(cmd,cmdlen,data,datalen,bmp->port,bmp->pin,bmp->bus,BMP_MS5607);
	return bmp->state;
}
*/





