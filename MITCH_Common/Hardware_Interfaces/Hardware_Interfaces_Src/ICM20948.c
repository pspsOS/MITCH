/*
 * ICM20948.c
 *
 *  Created on: Mar 28, 2021
 *      Author: jackwiley
 */

#include "generic_interface.h"
#include "ICM20948.h"
#include <stdio.h>

genericSensor_t ICM20948_init(SPI_HandleTypeDef *bus, GPIO_TypeDef *port, uint16_t pin)
{
	/** Define MS5607 Struct **/
	    ICM20948_t _imu = {0};
		genericSensor_t gIMU = {0};

		gIMU.sensorType = IMU_ICM20948;
		gIMU.sensor.ICM20948 = _imu;
		gIMU.read = ICM20948_read;
	//#ifndef __NO_HAL_SPI
		gIMU.interface.SPI.bus = bus;
		gIMU.interface.SPI.port = port;
		gIMU.interface.SPI.pin = pin;
		gIMU.interface.SPI.timeout = HAL_MAX_DELAY;

		gIMU.state = HAL_ERROR;
	//#endif
		gIMU.hasUpdate = true;
		gIMU.lock = false;



	#ifndef __NO_HAL_SPI
tryagain:
		//hello
gIMU.lock = false;

volatile ICM20948_t* imu;
		imu= &(gIMU.sensor.ICM20948);

		uint8_t whoami = 0xEA;
		uint8_t test = ICM_WHOAMI(imu);
		if(test == whoami) {
			printf("WHO AM I PASSED\n\r");
			    ICM_CSHigh(imu);
				HAL_Delay(10);
				ICM_SelectBank(USER_BANK_0,imu);
				HAL_Delay(10);
				ICM_Disable_I2C(imu);
				HAL_Delay(10);
				ICM_SetClock((uint8_t)CLK_BEST_AVAIL,imu);
				HAL_Delay(10);
				ICM_AccelGyroOff(imu);
				HAL_Delay(20);
				ICM_AccelGyroOn(imu);
				HAL_Delay(10);
				ICM_Initialize(imu);
				ICM_CSHigh(imu);
				gIMU.state = HAL_OK;
		}
		else
		{
			printf("Who AM I FAILED\r\n");
			HAL_Delay(1000);
		}
		if (gIMU.state==HAL_ERROR)
			goto tryagain;
	#endif
		// Update with all values

		return gIMU;


}
void ICM_readBytes(uint8_t reg, uint8_t *pData, uint16_t Size,genericSensor_t* sensor) // ***
{

	SPI_t* SPI = &(sensor->interface.SPI);
	reg = reg | 0x80;
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_RESET);
	receiveSPI(sensor, &reg, 1, pData, Size);
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_SET);
}

void ICM_WriteBytes(uint8_t reg, uint8_t *pData, uint16_t Size,genericSensor_t* sensor) // ***
{
	SPI_t* SPI = &(sensor->interface.SPI);
	reg = reg & 0x7F;
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_RESET);
	sendSPI(sensor, &reg, 1);
	sendSPI(sensor, pData, Size);
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_SET);

}

void ICM_ReadOneByte(uint8_t reg, uint8_t* pData,genericSensor_t* sensor) // ***
{
	SPI_t* SPI = &(sensor->interface.SPI);
	reg = reg | 0x80;
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_RESET);
	receiveSPI(sensor, &reg, 1, pData, 1);
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_SET);
}

void ICM_WriteOneByte(uint8_t reg, uint8_t Data,genericSensor_t* sensor) // ***
{

	SPI_t* SPI = &(sensor->interface.SPI);
	reg = reg & 0x7F;
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_RESET);
	sendSPI(sensor, &reg, 1);
	sendSPI(sensor, &Data, 1);
	HAL_GPIO_WritePin(SPI->port, SPI->pin, GPIO_PIN_SET);

}

/*
 *
 * AUX I2C abstraction for magnetometer
 *
 */
void i2c_Mag_write(uint8_t reg,uint8_t value,genericSensor_t* sensor)
  {
  	ICM_WriteOneByte(0x7F, 0x30,sensor);

  	HAL_Delay(1);
  	ICM_WriteOneByte(0x03 ,0x0C,sensor);//mode: write

  	HAL_Delay(1);
  	ICM_WriteOneByte(0x04 ,reg,sensor);//set reg addr

  	HAL_Delay(1);
  	ICM_WriteOneByte(0x06 ,value,sensor);//send value

  	HAL_Delay(1);
  }

  static uint8_t ICM_Mag_Read(uint8_t reg,genericSensor_t* sensor)
  {
  	uint8_t  Data;
  	ICM_WriteOneByte(0x7F, 0x30,sensor);
    HAL_Delay(1);
  	ICM_WriteOneByte(0x03 ,0x0C|0x80,sensor);
    HAL_Delay(1);
  	ICM_WriteOneByte(0x04 ,reg,sensor);// set reg addr
    HAL_Delay(1);
  	ICM_WriteOneByte(0x06 ,0xff,sensor);//read
  	HAL_Delay(1);
  	ICM_WriteOneByte(0x7F, 0x00,sensor);
  	ICM_ReadOneByte(0x3B,&Data,sensor);
    HAL_Delay(1);
  	return Data;
  }

  void ICM20948_READ_MAG(int16_t magn[3],genericSensor_t* sensor)
  {
    uint8_t mag_buffer[10];

      mag_buffer[0] =ICM_Mag_Read(0x01,sensor);

      mag_buffer[1] =ICM_Mag_Read(0x11,sensor);
  	  mag_buffer[2] =ICM_Mag_Read(0x12,sensor);
  	  magn[0]=mag_buffer[1]|mag_buffer[2]<<8;
    	mag_buffer[3] =ICM_Mag_Read(0x13,sensor);
      mag_buffer[4] =ICM_Mag_Read(0x14,sensor);
    	magn[1]=mag_buffer[3]|mag_buffer[4]<<8;
  	 	mag_buffer[5] =ICM_Mag_Read(0x15,sensor);
      mag_buffer[6] =ICM_Mag_Read(0x16,sensor);
  		magn[2]=mag_buffer[5]|mag_buffer[6]<<8;

     	i2c_Mag_write(0x31,0x01,sensor);
  }

/*
 *
 * Read magnetometer
 *
 */
void ICM_ReadMag(int16_t magn[3],genericSensor_t* sensor) {
	uint8_t mag_buffer[10];

	      mag_buffer[0] =ICM_Mag_Read(0x01,sensor);

	      mag_buffer[1] =ICM_Mag_Read(0x11,sensor);
	  	  mag_buffer[2] =ICM_Mag_Read(0x12,sensor);
	  	  magn[0]=mag_buffer[1]|mag_buffer[2]<<8;
	    	mag_buffer[3] =ICM_Mag_Read(0x13,sensor);
	      mag_buffer[4] =ICM_Mag_Read(0x14,sensor);
	    	magn[1]=mag_buffer[3]|mag_buffer[4]<<8;
	  	 	mag_buffer[5] =ICM_Mag_Read(0x15,sensor);
	      mag_buffer[6] =ICM_Mag_Read(0x16,sensor);
	  		magn[2]=mag_buffer[5]|mag_buffer[6]<<8;

	     	i2c_Mag_write(0x31,0x01,sensor);
}

/*
 *
 * Sequence to setup ICM290948 as early as possible after power on
 *
 */

uint16_t ICM_Initialize(genericSensor_t* sensor) {
		ICM_SelectBank(USER_BANK_2,sensor);
		HAL_Delay(20);
		ICM_SetGyroRateLPF(GYRO_RATE_250, GYRO_LPF_17HZ,sensor);
		HAL_Delay(10);

		// Set gyroscope sample rate to 100hz (0x0A) in GYRO_SMPLRT_DIV register (0x00)
		ICM_WriteOneByte(0x00, 0x0A,sensor);
		HAL_Delay(10);

		// Set accelerometer low pass filter to 136hz (0x11) and the rate to 8G (0x04) in register ACCEL_CONFIG (0x14)
		ICM_WriteOneByte(0x14, (0x04 | 0x11),sensor);

		// Set accelerometer sample rate to 225hz (0x00) in ACCEL_SMPLRT_DIV_1 register (0x10)
		ICM_WriteOneByte(0x10, 0x00,sensor);
		HAL_Delay(10);

		// Set accelerometer sample rate to 100 hz (0x0A) in ACCEL_SMPLRT_DIV_2 register (0x11)
		ICM_WriteOneByte(0x11, 0x0A,sensor);
		HAL_Delay(10);

		ICM_SelectBank(USER_BANK_2,sensor);
		HAL_Delay(20);

		// Configure AUX_I2C Magnetometer (onboard ICM-20948)
		ICM_WriteOneByte(0x7F, 0x00,sensor); // Select user bank 0
		ICM_WriteOneByte(0x0F, 0x30,sensor); // INT Pin / Bypass Enable Configuration
		ICM_WriteOneByte(0x03, 0x20,sensor); // I2C_MST_EN
		ICM_WriteOneByte(0x7F, 0x30,sensor); // Select user bank 3
		ICM_WriteOneByte(0x01, 0x4D,sensor); // I2C Master mode and Speed 400 kHz
		ICM_WriteOneByte(0x02, 0x01,sensor); // I2C_SLV0 _DLY_ enable
		ICM_WriteOneByte(0x05, 0x81,sensor); // enable IIC	and EXT_SENS_DATA==1 Byte

		// Initialize magnetometer
		i2c_Mag_write(0x32, 0x01,sensor); // Reset AK8963
		HAL_Delay(1000);
		i2c_Mag_write(0x31, 0x02,sensor); // use i2c to set AK8963 working on Continuous measurement mode1 & 16-bit output

		return 1337;
	}

void ICM_ReadAccelGyro(genericSensor_t* sensor) {
	uint8_t raw_data[12];
	volatile ICM20948_t* imu = &(sensor->sensor.ICM20948);
	ICM_readBytes(0x2D, raw_data, 12,sensor);

	imu->accel_xout = (raw_data[0] << 8) | raw_data[1];
	imu->accel_yout = (raw_data[2] << 8) | raw_data[3];
	imu->accel_zout = (raw_data[4] << 8) | raw_data[5];

	imu->gyr_xout = (raw_data[6] << 8) | raw_data[7];
	imu->gyr_yout = (raw_data[8] << 8) | raw_data[9];
	imu->gyr_zout = (raw_data[10] << 8) | raw_data[11];

	imu->accel_xout = imu->accel_xout / 8;
	imu->accel_yout = imu->accel_yout / 8;
	imu->accel_zout = imu->accel_zout / 8;
	printf("X:%d\r\n",imu->accel_xout);
	printf("Y:%d\r\n",imu->accel_yout);
	printf("Z:%d\r\n",imu->accel_zout);
	imu->gyr_xout = imu->gyr_xout / 250;
	imu->gyr_yout = imu->gyr_yout / 250;
	imu->gyr_zout = imu->gyr_zout / 250;
}
void ICM_SelectBank(uint8_t bank,genericSensor_t* sensor) {
	ICM_WriteOneByte(USER_BANK_SEL, bank,sensor);
}
void ICM_Disable_I2C(genericSensor_t* sensor) {
	ICM_WriteOneByte(0x03, 0x78,sensor);
}
void ICM_CSHigh(genericSensor_t* sensor) {

	SPI_t* SPI = &(sensor->interface.SPI);

		HAL_GPIO_WritePin(SPI->port, SPI->pin,SET);

}
void ICM_CSLow(genericSensor_t* sensor) {

	SPI_t* SPI = &(sensor->interface.SPI);

		HAL_GPIO_WritePin(SPI->port, SPI->pin,RESET);

}
void ICM_SetClock(uint8_t clk,genericSensor_t* sensor) {
	ICM_WriteOneByte(PWR_MGMT_1, clk,sensor);
}
void ICM_AccelGyroOff(genericSensor_t* sensor) {
	ICM_WriteOneByte(PWR_MGMT_2, (0x38 | 0x07),sensor);
}
void ICM_AccelGyroOn(genericSensor_t* sensor) {
	ICM_WriteOneByte(0x07, (0x00 | 0x00),sensor);
}

void ICM_SetGyroRateLPF(uint8_t rate, uint8_t lpf,genericSensor_t* sensor) {
	ICM_WriteOneByte(GYRO_CONFIG_1, (rate|lpf),sensor);
}

uint8_t ICM_WHOAMI(genericSensor_t* sensor) {
	uint8_t spiData = 0x01;
	ICM_ReadOneByte(0x00, &spiData,sensor);
	return spiData;
}

uint8_t ICM20948_read(volatile genericSensor_t* sensor){
	ICM_CSLow(sensor);
	ICM_ReadAccelGyro(sensor);
	ICM_CSHigh(sensor);

}

