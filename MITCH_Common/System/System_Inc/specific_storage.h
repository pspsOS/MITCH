/*
 * specific_storage.h
 *
 *  Created on: Mar 18, 2021
 *      Author: vishv
 */

#ifndef SYSTEM_SYSTEM_INC_SPECIFIC_STORAGE_H_
#define SYSTEM_SYSTEM_INC_SPECIFIC_STORAGE_H_

#include "generic_storage.h"
#include "interface_structs.h"

#include <string.h>

#define RETRY_TAKE_DELAY (0)

/* Function */

void storeBmpData(bmpData_t * );
void storeAlaData(alaData_t * );

#endif /* SYSTEM_SYSTEM_INC_SPECIFIC_STORAGE_H_ */
