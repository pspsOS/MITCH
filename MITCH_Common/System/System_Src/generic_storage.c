/*
 * generic_storage.c
 *
 *  Created on: Mar 18, 2021
 *      Author: vishv
 */

#include "generic_storage.h"


/**
 * @brief Converts unsigned int to Unsigned VLQ
 * Used for data compression
 *
 * @author Vishnu Vijay
 * @date 2/3/21
 */
VLQ_t convertToUVLQ(uint32_t originalNum) {
	uint8_t newNumArray[sizeof(originalNum) + 1] = {0};
	uint8_t buffer = 0;
	int length = 0;
	do {
		buffer = (originalNum & 0x7F);

		buffer |= 0x80;

		newNumArray[length] = buffer;
		length++;
	} while ( originalNum >>= 7 );

	newNumArray[0] &= 0x7F;

	VLQ_t newNum = {0};
	newNum.quantityLength = length;
	for (int i = 0; i < length; i++) {
		switch (length) {
			case 1:
				newNum.oneByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 2:
				newNum.twoByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 3:
				newNum.threeByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 4:
				newNum.fourByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 5:
				newNum.fiveByteVLQ[i] = newNumArray[length - i - 1];
				break;
		}
	}

	return newNum;
}

/**
 * @brief Converts signed int to signed VLQ
 * Used for data compression
 *
 * @author Vishnu Vijay
 * @date 2/7/21
 */
VLQ_t convertToSVLQ(int32_t signedNum) {
	uint8_t newNumArray[sizeof(signedNum) + 1] = {0};
	uint8_t buffer = 0;
	uint32_t originalNum = 0;
	int length = 0;
	uint8_t firstByte = 1;
	if (signedNum < 0) {
		originalNum = signedNum * -1;
	}
	else {
		originalNum = signedNum;
	}


	do {
		if (length == 0) {
			buffer = (originalNum & 0x3F);
			if (signedNum < 0) {
				buffer |= 0x40;
			}
		}
		else {
			buffer = (originalNum & 0x7F);
			firstByte = 0;
		}
		buffer |= 0x80;
		newNumArray[length] = buffer;
		length++;
		printf("len: %d\tfb: %d\tnum: %X\n", length, firstByte, originalNum);
	} while ( originalNum >>= (7 - firstByte) );

	newNumArray[0] &= 0x7F;

	VLQ_t newNum = {0};
	newNum.quantityLength = length;
	for (int i = 0; i < length; i++) {
		switch (length) {
			case 1:
				newNum.oneByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 2:
				newNum.twoByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 3:
				newNum.threeByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 4:
				newNum.fourByteVLQ[i] = newNumArray[length - i - 1];
				break;
			case 5:
				newNum.fiveByteVLQ[i] = newNumArray[length - i - 1];
				break;
		}
	}

	return newNum;
}


/**
 * @brief Writes to file
 * Writes the pointer to a file
 *
 * @author Ryan Horvath
 * @date 2/11/21
 */
int8_t writeToStorage(uint8_t *bytePointer, uint8_t streamSize) {
#ifndef NDEBUG
	FILE *fp = NULL;

	// Binary
	fp = fopen("output_binary.bin", "a");
	if (fp == NULL) {
		return FAILED_FILE_WRITE;
	}
	fwrite(bytePointer, sizeof(uint8_t), streamSize, fp);
	fclose(fp);
	fp = NULL;

	// Hex
	fp = fopen("output_hex.txt", "a");
	if (fp == NULL) {
		return FAILED_FILE_WRITE;
	}
	for (int i = 0; i < streamSize; i++) {
		fprintf(fp, "%.2X-", bytePointer[i]);
	}
	fclose(fp);
	fp = NULL;
#endif
	return SUCCESSFUL_FILE_WRITE;
}
