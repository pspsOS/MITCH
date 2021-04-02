/*
 * generic_storage.h
 *
 *  Created on: Mar 18, 2021
 *      Author: vishv
 */

#ifndef SYSTEM_SYSTEM_INC_GENERIC_STORAGE_H_
#define SYSTEM_SYSTEM_INC_GENERIC_STORAGE_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>

/* Struct Typedef */

typedef struct VLQ {
	uint8_t quantityLength;
	union {
		uint8_t oneByteVLQ[1];
		uint8_t twoByteVLQ[2];
		uint8_t threeByteVLQ[3];
		uint8_t fourByteVLQ[4];
		uint8_t fiveByteVLQ[5];
	};
} VLQ_t;


/* Constants */

#define NOMINAL_DAQ_STATUS (0x80)
#define NOMINAL_GPS_DATA (0x90)
#define NOMINAL_BMP_DATA (0xA0)
#define NOMINAL_IMU_DATA (0xB0)
#define NOMINAL_MONITOR_DATA (0xC0)
#define NOMINAL_PROCESSED_DATA (0xD0)
#define NOMINAL_ALA_DATA (0xE0)

#define FAILED_FILE_WRITE (-1)
#define SUCCESSFUL_FILE_WRITE (0)


/* Function */

VLQ_t convertToUVLQ(uint32_t );
VLQ_t convertToSVLQ(int32_t );
int8_t writeToStorage(uint8_t *, uint8_t );


#endif /* SYSTEM_SYSTEM_INC_GENERIC_STORAGE_H_ */
