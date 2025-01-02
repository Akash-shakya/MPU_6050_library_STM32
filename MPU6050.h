/*
Header file for MPU6050 by Akash shakya 02/01/2025
*/
#ifndef _MPU6050_H_
#define _MPU6050_H_

/* Definitions --------------------------------------------------------------*/
#define MPU6050_ADDR        0x68	//Device Address
#define REG_WHO_AM_I        0x75	//This register is used to verify the identity of the device
#define REG_PWR_MGMT_1      0x6B	//configure the power mode and clock source
#define REG_SMPLRT_DIV      0x19	//This register specifies the divider from the gyroscope output rate used to generate the Sample Rate
#define REG_ACCEL_CONFIG    0x1C	//Accelerometer Configuration
#define REG_GYRO_CONFIG     0x1B	//Gyroscope Configuration
#define REG_GYRO_XOUT_H     0x43	//Gyroscope Measurements
#define REG_ACCEL_XOUT_H    0x3B	//Accelerometer Measurements
#define REG_TEMP_OUT_H		0x41	//Temperature Measurement

// Structure to hold accelerometer data and gyroscope data
typedef struct {
    float Gyro_X;  // Gyroscope X-axis value
    float Gyro_Y;  // Gyroscope Y-axis value
    float Gyro_Z;  // Gyroscope Z-axis value
} GyroscopeData;

typedef struct {
    float Accel_X;  // Accelerometer X-axis value
    float Accel_Y;  // Accelerometer Y-axis value
    float Accel_Z;  // Accelerometer Z-axis value
} AccelerometerData;


/*************Function declaration ***************************/
void mupu6050_init(void);
void MPU_Accel_Read();
void MPU_Gyro_Read();
void MPU_Temp_read();

#endif
