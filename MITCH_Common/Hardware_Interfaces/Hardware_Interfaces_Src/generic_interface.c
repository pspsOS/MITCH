/*
 * generic_interface.c
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */


#include "generic_interface.h"

void bmpInit(genericBMP_t* bmp) {
	switch(bmp->bmpType) {
	case BMP_MS5607:

		break;
	default:
		printf("Invalid bmp init attempted");
		break;
	}
}


void bmpRead(genericBMP_t* bmp);
