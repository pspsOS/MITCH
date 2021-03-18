/*
 * NucleoButton.h
 *
 *  Created on: Mar 17, 2021
 *      Author: Jeff
 */

#ifndef NUCLEOBUTTON_H_
#define NUCLEOBUTTON_H_

genericDevice_t button_init(GPIO_TypeDef *port, uint16_t pin);
HAL_StatusTypeDef button_read(genericDevice_t* device);

#endif /* NUCLEOBUTTON_H_ */
