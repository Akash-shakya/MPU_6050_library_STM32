/*
C file for MPU6050 by Akash shakya 02/01/2025
*/
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "MPU6050.h"
#include "stm32f4xx_hal.h" // Include HAL library for STM32

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

char msg[100];

void mupu6050_init()
{
	 HAL_StatusTypeDef ret =  HAL_I2C_IsDeviceReady(&hi2c1, MPU6050_ADDR<<1 , 1,100);
	  //The address is shifted left by 1 bit to make room for the read/write (R/W) bit.
	 // For example, 0x68 (7-bit address) becomes 0xD0 when shifted left (0x68 << 1 = 0xD0).
		  if(ret == HAL_OK)
		  {
			sprintf(msg, "Device is ready\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }
		  else
		  {
			sprintf(msg,"Device is not ready \r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }

	//HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
		  //uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	  uint8_t gyrodata = 0b00001000;  //Config Gyroscope
	  HAL_StatusTypeDef retvalue =  HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR<<1, REG_GYRO_CONFIG , 1, &gyrodata, 1, 100);
		  if(retvalue == HAL_OK)
		  {
			sprintf(msg, "gyroscope Configuration successfully \r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }
		  else
		  {
			sprintf(msg,"gyroscope Configuration failed \r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }

	  uint8_t accdata = 0b00001000;  //Accelerometer Configuration
	  HAL_StatusTypeDef retvalueacc =  HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR<<1, REG_ACCEL_CONFIG , 1, &accdata, 1, 100);
		  if(retvalueacc == HAL_OK)
		  {
			sprintf(msg, "Accelerometer Configuration successfully \r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }
		  else
		  {
			sprintf(msg,"Accelerometer Configuration failed \r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }

	  uint8_t powdata = 0b00000000;  //Accelerometer Configuration
	  HAL_StatusTypeDef retvaluepow =  HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR<<1, REG_PWR_MGMT_1 , 1, &powdata, 1, 100);
		  if(retvaluepow == HAL_OK)
		  {
			sprintf(msg, "Power Management 1 Configuration successfully \r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }
		  else
		  {
			sprintf(msg,"Power Management 1 Configuration failed \r\n");
			HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		  }
}

void MPU_Accel_Read(AccelerometerData *Mpu_Accel)
{
    uint8_t Read_Data[6];

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR<<1, REG_ACCEL_XOUT_H, 1, Read_Data, 6, 100);

    int16_t Accel_X_RAW = ((int16_t)Read_Data[0] << 8) + Read_Data[1];
    int16_t Accel_Y_RAW = ((int16_t)Read_Data[2] << 8) + Read_Data[3];
    int16_t Accel_Z_RAW = ((int16_t)Read_Data[4] << 8) + Read_Data[5];

    Mpu_Accel->Accel_X = Accel_X_RAW / 16384.0;  //  X-axis acceleration
    Mpu_Accel->Accel_Y = Accel_Y_RAW / 16384.0; //  Y-axis acceleration
    Mpu_Accel->Accel_Z = Accel_Z_RAW / 16384.0;  //  Z-axis acceleration
}

void MPU_Gyro_Read(GyroscopeData *Mpu_Gyro)
{
    uint8_t Read_Data[6];

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR<<1, REG_GYRO_XOUT_H, 1, Read_Data, 6, 100);

    int16_t Gyro_X_RAW = ((int16_t)Read_Data[0] << 8) + Read_Data[1];
    int16_t Gyro_Y_RAW = ((int16_t)Read_Data[2] << 8) + Read_Data[3];
    int16_t Gyro_Z_RAW = ((int16_t)Read_Data[4] << 8) + Read_Data[5];

    Mpu_Gyro->Gyro_X = Gyro_X_RAW / 131.0;  //  X-axis Gyroscope
    Mpu_Gyro->Gyro_Y = Gyro_Y_RAW / 131.0; //  Y-axis Gyroscope
    Mpu_Gyro->Gyro_Z = Gyro_Z_RAW / 131.0;  //  Z-axis Gyroscope

}

void MPU_Temp_read()
{
    uint8_t Read_Data[2];

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR<<1, REG_TEMP_OUT_H, 1, Read_Data, 2, 100);

    int16_t Temp_RAW = ((int16_t)Read_Data[0] << 8) + Read_Data[1];
    float temp = (Temp_RAW/340)+ 36.53;
    sprintf(msg,"Temperature  : %f \r\n",temp);
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}
