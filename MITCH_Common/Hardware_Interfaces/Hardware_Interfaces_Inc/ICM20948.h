/*
 * ICM20948.h
 *
 *  Created on: Mar 28, 2021
 *      Author: jackwiley
 */

#ifndef HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_ICM20948_H_
#define HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_ICM20948_H_

#define USER_BANK_SEL	(0x7F)
#define USER_BANK_0		(0x00)
#define USER_BANK_1		(0x10)
#define USER_BANK_2		(0x20)
#define USER_BANK_3		(0x30)

#define PWR_MGMT_1 		(0x06)
#define PWR_MGMT_2		(0x07)
#define GYRO_CONFIG_1	(0x01)


#define CLK_BEST_AVAIL	(0x01)
#define GYRO_RATE_250	(0x00)
#define GYRO_LPF_17HZ 	(0x29)

void ICM_SelectBank(uint8_t bank,genericSensor_t* sensor);
void ICM_ReadAccelGyro(genericSensor_t* sensor);
void ICM_ReadMag(int16_t magn[3],genericSensor_t* sensor);
uint16_t ICM_Initialize(genericSensor_t* sensor);
void ICM_SelectBank(uint8_t bank,genericSensor_t* sensor);
void ICM_Disable_I2C(genericSensor_t* sensor);
void ICM_CSHigh(genericSensor_t* sensor);
void ICM_CSLow(genericSensor_t* sensor);
void ICM_SetClock(uint8_t clk,genericSensor_t* sensor);
void ICM_AccelGyroOff(genericSensor_t* sensor);
void ICM_AccelGyroOn(genericSensor_t* sensor);
void ICM_SetGyroRateLPF(uint8_t rate, uint8_t lpf,genericSensor_t* sensor);
void ICM_SetGyroLPF(uint8_t lpf,genericSensor_t* sensor);
uint8_t ICM_WHOAMI(genericSensor_t* sensor);

volatile genericSensor_t ICM20948_init(SPI_HandleTypeDef *bus, GPIO_TypeDef *port, uint16_t pin);
uint8_t ICM20948_read(volatile genericSensor_t* sensor);
#endif /* HARDWARE_INTERFACES_HARDWARE_INTERFACES_INC_ICM20948_H_ */
