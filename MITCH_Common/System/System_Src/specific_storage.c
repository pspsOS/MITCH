/*
 * specific_storage.c
 *
 *  Created on: Mar 25, 2021
 *      Author: vishv
 */


#include "specific_storage.h"


/**
 * @brief stores BMP data
 * Stores values from the bmpData Struct
 *
 * @author Ryan Horvath, Vishnu Vijay
 * @date 1/30/21
 */
void storeBmpData(bmpData_t *dataToStore) {
	if (dataToStore->lock) {
			retryTakeDelay(DEFAULT_TAKE_DELAY);
	}
	dataToStore->lock = true;

	uint8_t dataStream[16] = {0};
	dataStream[0] = NOMINAL_BMP_DATA;
	uint8_t size = 1;

	//Compressing Time Stamp
	VLQ_t genericVLQ = convertToUVLQ(dataToStore->timeStamp);
	for (uint8_t i = size; i < genericVLQ.quantityLength + size; i++) {
		switch (genericVLQ.quantityLength) {
			case 1:
				dataStream[i] = genericVLQ.oneByteVLQ[i - size];
				break;
			case 2:
				dataStream[i] = genericVLQ.twoByteVLQ[i - size];
				break;
			case 3:
				dataStream[i] = genericVLQ.threeByteVLQ[i - size];
				break;
			case 4:
				dataStream[i] = genericVLQ.fourByteVLQ[i - size];
				break;
		}
	}
	size += genericVLQ.quantityLength;

	//printf("BMP Time Stamp: %X\n", dataToStore->timeStamp);

	//Compressing Pressure
	memset(&genericVLQ, 0, sizeof(genericVLQ));
	genericVLQ = convertToSVLQ(dataToStore->pressure);
	for (uint8_t i = size; i < genericVLQ.quantityLength + size; i++) {
		switch (genericVLQ.quantityLength) {
			case 1:
				dataStream[i] = genericVLQ.oneByteVLQ[i - size];
				break;
			case 2:
				dataStream[i] = genericVLQ.twoByteVLQ[i - size];
				break;
			case 3:
				dataStream[i] = genericVLQ.threeByteVLQ[i - size];
				break;
			case 4:
				dataStream[i] = genericVLQ.fourByteVLQ[i - size];
				break;
		}
	}
	size += genericVLQ.quantityLength;

	//Compressing Temperature
	memset(&genericVLQ, 0, sizeof(genericVLQ));
	genericVLQ = convertToSVLQ(dataToStore->temperature);
	for (uint8_t i = size; i < genericVLQ.quantityLength + size; i++) {
		switch (genericVLQ.quantityLength) {
			case 1:
				dataStream[i] = genericVLQ.oneByteVLQ[i - size];
				break;
			case 2:
				dataStream[i] = genericVLQ.twoByteVLQ[i - size];
				break;
			case 3:
				dataStream[i] = genericVLQ.threeByteVLQ[i - size];
				break;
			case 4:
				dataStream[i] = genericVLQ.fourByteVLQ[i - size];
				break;
		}
	}
	size += genericVLQ.quantityLength;

	dataToStore->lock = false;

	uint8_t funcReturn = writeToStorage(dataStream, size);
	if (funcReturn == FAILED_FILE_WRITE) {
		printf("Failed File Write\n");
	}
	else if (funcReturn == SUCCESSFUL_FILE_WRITE) {
		printf("Successful File Write\n");
	}
}



/**
 * @brief stores ALA data
 * Stores values from the alaData Struct
 *
 * @author Ryan Horvath, Vishnu Vijay
 * @date 1/30/21
 */
void storeAlaData(alaData_t *dataToStore) {
	if (dataToStore->lock) {
			retryTakeDelay(DEFAULT_TAKE_DELAY);
	}
	dataToStore->lock = true;

	uint8_t dataStream[12] = {0};
	dataStream[0] = NOMINAL_ALA_DATA;
	uint8_t size = 1;

	//Compressing Time Stamp
	VLQ_t genericVLQ = convertToUVLQ(dataToStore->timeStamp);
	for (uint8_t i = size; i < genericVLQ.quantityLength + size; i++) {
		switch (genericVLQ.quantityLength) {
			case 1:
				dataStream[i] = genericVLQ.oneByteVLQ[i - size];
				break;
			case 2:
				dataStream[i] = genericVLQ.twoByteVLQ[i - size];
				break;
			case 3:
				dataStream[i] = genericVLQ.threeByteVLQ[i - size];
				break;
			case 4:
				dataStream[i] = genericVLQ.fourByteVLQ[i - size];
				break;
		}
	}
	size += genericVLQ.quantityLength;

	//printf("ALA Time Stamp: %X\n", dataToStore->timeStamp);

	//Compressing Measured
	memset(&genericVLQ, 0, sizeof(genericVLQ));
	genericVLQ = convertToSVLQ(dataToStore->meas);
	for (uint8_t i = size; i < genericVLQ.quantityLength + size; i++) {
		switch (genericVLQ.quantityLength) {
			case 1:
				dataStream[i] = genericVLQ.oneByteVLQ[i - size];
				break;
			case 2:
				dataStream[i] = genericVLQ.twoByteVLQ[i - size];
				break;
			case 3:
				dataStream[i] = genericVLQ.threeByteVLQ[i - size];
				break;
			case 4:
				dataStream[i] = genericVLQ.fourByteVLQ[i - size];
				break;
		}
	}
	size += genericVLQ.quantityLength;

	//Compressing Reference
	memset(&genericVLQ, 0, sizeof(genericVLQ));
	genericVLQ = convertToSVLQ(dataToStore->ref);
	for (uint8_t i = size; i < genericVLQ.quantityLength + size; i++) {
		switch (genericVLQ.quantityLength) {
			case 1:
				dataStream[i] = genericVLQ.oneByteVLQ[i - size];
				break;
			case 2:
				dataStream[i] = genericVLQ.twoByteVLQ[i - size];
				break;
			case 3:
				dataStream[i] = genericVLQ.threeByteVLQ[i - size];
				break;
			case 4:
				dataStream[i] = genericVLQ.fourByteVLQ[i - size];
				break;
		}
	}
	size += genericVLQ.quantityLength;

	dataToStore->lock = false;

	uint8_t funcReturn = writeToStorage(dataStream, size);
	if (funcReturn == FAILED_FILE_WRITE) {
		printf("Failed File Write\n");
	}
	else if (funcReturn == SUCCESSFUL_FILE_WRITE) {
		printf("Successful File Write\n");
	}
}
