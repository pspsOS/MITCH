/*
 * gps_acquistion.c
 *
 *  Created on: Mar 7, 2021
 *      Author: Jeff
 */


#include "gps_acquisition.h"
#include "generic_interface.h"
#include "interface_structs.h"
#include "system_functions.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Local variable declarations */
char gpsNmea[MAX_NMEA]; // Buffer that holds GPS String
char unsplitGpsNmea[MAX_NMEA]; // Buffer that holds GPS String and is not split
bool gpsNominal;        // Indicates whether the GPS is nominal


uint8_t _nmeaAddrStart;
uint8_t _nmeaAddrEnd;

// File pointers for Debugging
#ifdef HARDWARE_EMULATOR
	FILE *_gpsFile;
#endif

void gpsSetup_A() {
	gpsNominal = true;
		#ifdef HARDWARE_EMULATOR
			//_gpsFile = setupSensorFile_DS(GPS, &gpsNominal);
		#else
			// TODO: Implement gpsSetup
			//gpsInit(&gpsNominal);
			//notify(TASK_UPDATE, GPS);
		#endif
}


/** gpsRead_A()
 * @brief GPS Read
 * Read data from GPS
 *
 * @param None
 * @retval None
 *
 * @author Jack Wiley
 * @date 02/01/2021
 */
void gpsRead_A(gpsData_t* g_gpsData) {
#ifdef BYPASS_GPS
	printf("GPS Read \r\n");
	return;
#endif
	// local variables
	int time; //holds value to compare
	bool firstFlag; // flag signaling function is being called the first time

	firstFlag = false;


	// loads in data
	_loadGpsData();
	strncpy((char*)unsplitGpsNmea, gpsNmea, strlen(gpsNmea));

	_splitNmea();

	//recieving no new data
	if((!strcmp((char*)g_gpsData->nmeaGGA, unsplitGpsNmea) || !strcmp((char*)g_gpsData->nmeaRMC, unsplitGpsNmea)))
	{
		g_gpsData->hasUpdate = false;
		// leave function
		return;
	}



	//lock structure
	while(g_gpsData->lock)
	#ifndef HARDWARE_EMULATOR
		retryTakeDelay(DEFAULT_TAKE_DELAY);
	#else
		break;
	#endif
	g_gpsData->lock = true;



	// first time loading in
	if((!strcmp((char*)g_gpsData->nmeaGGA, "") && !strcmp((char*)g_gpsData->nmeaRMC, "")))
	{
		_addNmeaData();

		//load next packet
		_loadGpsData();
		strncpy((char*)unsplitGpsNmea, gpsNmea, strlen(gpsNmea));
		_splitNmea();

		firstFlag = true;

	}

	//if no unsent data
	if((strcmp((char*)g_gpsData->nmeaGGA, "") && strcmp((char*)g_gpsData->nmeaRMC, "")) && !firstFlag)
	{


		_addNmeaData();
		//load next packet
		_loadGpsData();
		strncpy((char*)unsplitGpsNmea, gpsNmea, strlen(gpsNmea));
		_splitNmea();

		//recieving no new data
		if((!strcmp((char*)g_gpsData->nmeaGGA, unsplitGpsNmea) || !strcmp((char*)g_gpsData->nmeaRMC, unsplitGpsNmea)))
		{
			g_gpsData->hasUpdate = false;
			// leave function
			return;
		}

		time = 0;
		_findNmeaAddr(1);
		time = atoi(&gpsNmea[_nmeaAddrStart]);

		//printf("%d\n",g_gpsData->utc);
		if(time == g_gpsData->utc )
		{
			//printf("here\n");
			// if time stamps are equal
			_addNmeaData();

			g_gpsData->hasUpdate = true;

			//unlocking
			g_gpsData->lock = false;

			__printGpsData();

		}
		else
		{

			// time stamps are different

			// setting unreciveced data to zero
			if((strcmp((char*)g_gpsData->nmeaGGA, "")))
			{
				//never recieved rmc
				//strncpy((char*)g_gpsData->nmeaRMC, "", 0);
				_clearNmea((char*)&g_gpsData->nmeaRMC);
				g_gpsData->speed = 0.0;

			}
			else
			{
				//never recieved gga
				//strncpy((char*)g_gpsData->nmeaGGA, "", 0);
				_clearNmea((char*)&g_gpsData->nmeaGGA);
				g_gpsData->alt = 0.0;
				g_gpsData->fix = 0;

			}


			//unlocking
			g_gpsData->hasUpdate = true;
			g_gpsData->lock = false;
			__printGpsData();
			do {
			#ifndef HARDWARE_EMULATOR
				retryTakeDelay(DEFAULT_TAKE_DELAY);
			#else
				g_gpsData->hasUpdate = false; // Breaks infinite loop if run in testbed
			#endif
			} while(g_gpsData->hasUpdate || g_gpsData->lock);

			//relock
			while(g_gpsData->lock)
			#ifndef HARDWARE_EMULATOR
				retryTakeDelay(DEFAULT_TAKE_DELAY);
			#else
				break;
			#endif
			g_gpsData->lock = true;

			_addNmeaData();


			// setting unreciveced data to zero
			if(!_getNmeaType())
			{

				//never recieved gga
				//strncpy((char*)g_gpsData->nmeaGGA, "", 0);
				_clearNmea((char*)&g_gpsData->nmeaGGA);
				g_gpsData->alt = 0.0;
				g_gpsData->fix = 0;

			}
			else
			{
				//never recieved rmc
				//strncpy((char*)g_gpsData->nmeaRMC, "", 0);
				_clearNmea((char*)&g_gpsData->nmeaRMC);
				g_gpsData->speed = 0.0;

			}

			//unlock
			g_gpsData->hasUpdate = false;
			g_gpsData->lock = false;


		}
	} else {

		// unsent data in struct
		time = 0;
		_findNmeaAddr(1);
		time = atoi(&gpsNmea[_nmeaAddrStart]);

		if(time == g_gpsData->utc ) {

			// if time stamps are equal
			_addNmeaData();

			g_gpsData->hasUpdate = true;

			//unlocking
			g_gpsData->lock = false;
			__printGpsData();


	    } else {

			//timestamps are different

			//unlocking
				g_gpsData->hasUpdate = true; // This sets hasUpdate = true
				g_gpsData->lock = false;
				__printGpsData();
				do {
				#ifndef HARDWARE_EMULATOR
					retryTakeDelay(DEFAULT_TAKE_DELAY);
				#else
					g_gpsData->hasUpdate = false; // Breaks infinite loop if run in testbed
				#endif
				} while(g_gpsData->hasUpdate || g_gpsData->lock);

				//relock
				while(g_gpsData->lock)
				#ifndef HARDWARE_EMULATOR
					retryTakeDelay(DEFAULT_TAKE_DELAY);
				#else
					break;
				#endif

				_addNmeaData();


				// setting unreciveced data to zero
				if(!_getNmeaType())
				{

					//never recieved rmc
					//strncpy((char*)g_gpsData->nmeaRMC, "", 0);
					_clearNmea((char*)&g_gpsData->nmeaRMC);
					g_gpsData->speed = 0.0;

				}
				else
				{

					//never recieved gga
					//strncpy((char*)g_gpsData->nmeaGGA, "", 0);
					_clearNmea((char*)&g_gpsData->nmeaGGA);
					g_gpsData->alt = 0.0;
					g_gpsData->fix = 0;

				}

				//unlock
				g_gpsData->hasUpdate = false;
				g_gpsData->lock = false;

		}
	}
}


/**
 * @brief adds Nmea data to struct
 * gets nmea varaibles from the string and adds variables to struct depending on Nmea type
 *
 * @param None
 * @retval None
 *
 * @author Jack Wiley
 * @date 1/25/2020
 */

void _addNmeaData(gpsData_t* g_gpsData)
{
	// local variables
	int time; //holds value until copied into struct
	float altitude;  //holds value until copied into struct
	float speed; //holds value until copied into struct
	int fix; //holds value until copied into struct

	if(!_getNmeaType())
			{
		//Type GGA
		//adds GCA to struct
		strncpy((char*)g_gpsData->nmeaGGA, unsplitGpsNmea, strlen(unsplitGpsNmea));

		//adds time to stuct
		time = 0;
		_findNmeaAddr(1);
		time = atoi(&gpsNmea[_nmeaAddrStart]);

		g_gpsData->utc = time;
		g_gpsData->timeStamp = getTimeStamp();


		//adds altitude to struct
		altitude = 0;
		_findNmeaAddr(9);
		altitude = atof(&gpsNmea[_nmeaAddrStart]);
		g_gpsData->alt = altitude;

		//adds fix to struct
		fix = 0;
		_findNmeaAddr(6);
		fix = atof(&gpsNmea[_nmeaAddrStart]);
		g_gpsData->fix = fix;

	}
	else
	{
		//Type RMC
		strncpy((char*)g_gpsData->nmeaRMC, unsplitGpsNmea, strlen(unsplitGpsNmea));

		//adds time to stuct
		time = 0;
		_findNmeaAddr(1);
		time = atoi(&gpsNmea[_nmeaAddrStart]);
		g_gpsData->utc = time;
		g_gpsData->timeStamp = getTimeStamp();

		//adds speed to struct
		speed = 0;
		_findNmeaAddr(7);
		speed = atof(&gpsNmea[_nmeaAddrStart]);
		g_gpsData->speed = speed;



	}


}


/**
 * @brief gets the Nmea type
 * returns 0 if the Nmea is GCC, and 1 if the Nmea is RMC
 *
 * @param None
 * @retval type, 1 or 0 depending on description above
 *
 * @author Jack Wiley
 * @date 1/25/2020
 */
int _getNmeaType()
{

	//	Type = GPGGA
	if (!(strncmp(&gpsNmea[0], "$GPGGA", 6))) {
		return 0;
	}
		//	Type = GPRMC
	else
	{
		return 1;
	}

}

/**
 * @brief Loads Gps Data
 * Takes data from either hardware or text file depending on if debuging
 *
 * @param None
 * @retval None
 *
 * @author Jack Wiley
 * @date 1/25/2020
 */
void _loadGpsData()
{
#ifdef HARDWARE_EMULATOR
	/*
		if(!simulateGps) {
			if(notifyWhenReadAborted)
				printf("GPS read aborted.\n");
			return;
		}
		fscanf(_gpsFile, "%s", gpsNmea);
	#else
		//TODO: Implement gpsRead w/ hardware
		//gpsLoadString(gpsNmea);
*/
	#endif
}

/**
 * @brief Split NMEA String
 * Takes raw NMEA string and replaces ',' with 0, splitting each substring
 *
 * @param None
 * @retval None
 *
 * @author Jeff Kaji
 * @date 12/26/2020
 */
void _splitNmea() {
	for(int i = 0; i < 80; i++) {
		if(gpsNmea[i] == ',')
			gpsNmea[i] = 0;
		else if(gpsNmea[i] == 0)
			return;
	}
}

/**
 * @brief NMEA Address Identification
 * Finds the start and end addresses of a given field within split string gpsNmea.
 *   Stores start address in _nmeaAddrStart
 *   Stores end address in _nmeaAddrEnd
 *
 * @param addr: Address to locate
 * @retval None
 *
 * @author Jeff Kaji
 * @date 12/25/2020
 */
void _findNmeaAddr(int addr) {
    for(int i = 0; i < 80; i++) {

    	// Find instance of ','
        if(gpsNmea[i] == 0) {
            addr -= 1;

            // Set end address
            if(addr == -1) {
                _nmeaAddrEnd = i;
                break;
            }

            // Set start address
            _nmeaAddrStart = i+1;
        }
    }
}

void _clearNmea(char *nmea) {
	for(int i = 0; i < MAX_NMEA; i++)
		nmea[i] = 0;
}

// Test Functions


/**
 * @brief Prints Gps Data
 *
 * @param None
 * @retval None
 *
 * @author Jack Wiley
 * @date 1/26/2020
 */
void __printGpsData(gpsData_t* g_gpsData)
{

	printf("Time: %d\n",g_gpsData->utc);
	printf("GGA: %s\n",g_gpsData->nmeaGGA);
	printf("RMC: %s\n",g_gpsData->nmeaRMC);
	printf("Fix: %d\n",g_gpsData->fix);
	//printf("Alt: %f\n",g_gpsData->alt)	;
	//printf("Speed: %f\n\n",g_gpsData->speed);
}

/**
 * @brief Set Local NMEA String
 * Sets the local string gpsNmea[80] to the input string.
 * As of now, is only intended for use in the testbed.
 *
 * @param nmea: New value for local string
 * @retval None
 *
 * @author Jeff Kaji
 * @date 12/26/2020
 */
void __setNmea(char *nmea) {
	strncpy(gpsNmea, nmea, strlen(nmea));
}

/**
 * @brief Prints NMEA string
 * printf NMEA string to console. Used for debugging.
 *
 * @param None
 * @retval None
 *
 * @author Jeff Kaji
 * @date 12/26/2020
 */
void __printNmea() {
	printf("\n%s", gpsNmea);
}


