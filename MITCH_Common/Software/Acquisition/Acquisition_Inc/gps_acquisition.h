/*
 * gps_acquisition.h
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */

#ifndef SOFTWARE_ACQUISITION_ACQUISITION_INC_GPS_ACQUISITION_H_
#define SOFTWARE_ACQUISITION_ACQUISITION_INC_GPS_ACQUISITION_H_

#include "acquisition.h"

void gpsSetup_A();
void gpsRead_A();
void _splitNmea();
void _findNmeaAddr(int addr);
void _loadGpsData();
int _getNmeaType();
void _addNmeaData();
void _clearNmea(char*);

//Test Function
void __printGpsData();

void __setNmea(char *nmea);
void __printNmea();

float __getFloat(int addr);



#endif /* SOFTWARE_ACQUISITION_ACQUISITION_INC_GPS_ACQUISITION_H_ */
