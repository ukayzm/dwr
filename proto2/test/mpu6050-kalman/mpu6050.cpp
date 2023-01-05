/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

#include "Arduino.h"
#include <Wire.h>
#include "mpu6050.h"


#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter
Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;
double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter


/* IMU Data */
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;

double gyroXangle, gyroYangle; // Angle calculate using the gyro only

uint32_t prev_micros;
uint8_t i2cData[14]; // Buffer for I2C data

const int MPU_addr=0x68;
#define MPU6050_CONFIG_1

double temperature;

// TODO: Make calibration routine

void setup_mpu6050() {
	Wire.begin();
#if defined(MPU6050_CONFIG_1)
	TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz

	Wire.beginTransmission(MPU_addr);
	Wire.write(0x19);
	Wire.write(7);    // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
	Wire.write(0x00); // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
	Wire.write(0x00); // Set Gyro Full Scale Range to ±250deg/s
	Wire.write(0x00); // Set Accelerometer Full Scale Range to ±2g
	Wire.endTransmission(false);

	/* PLL with X axis gyroscope reference and disable sleep mode */
	Wire.beginTransmission(MPU_addr);
	Wire.write(0x6B);
	Wire.write(0x01);
	Wire.endTransmission(true);
#else
	Wire.beginTransmission(MPU_addr);
	Wire.write(0x6B);
	Wire.write(0);
	Wire.endTransmission(true);
#endif

	delay(100); // Wait for sensor to stabilize

	/* Set kalman and gyro starting angle */
	Wire.beginTransmission(0x68);
	Wire.write(0x3B);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU_addr, 6, true);
	accX = Wire.read()<<8 | Wire.read();
	accY = Wire.read()<<8 | Wire.read();
	accZ = Wire.read()<<8 | Wire.read();

	// Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
	// atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
	// It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
	double roll  = atan2(accY, accZ) * RAD_TO_DEG;
	double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
	double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
	double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

	kalmanX.setAngle(roll); // Set starting angle
	kalmanY.setAngle(pitch);
	gyroXangle = roll;
	gyroYangle = pitch;

	Serial.println("MPU6050 initialized");

	prev_micros = micros();
}


#if defined(CHECK_ELAPSED_TIME)
unsigned long start_usec;
unsigned long elapsed1_usec;
unsigned long elapsed2_usec;
unsigned long elapsed3_usec;
unsigned long elapsed4_usec;
#endif

/*
 * output of loop_mpu6050():
 *
 * roll: X angle by accelerometer
 * gyroXangle: X angle by gyroscope
 * compAngleX: X angle by complementary filter
 * kalAngleX: X angle by Kalman filter
 * pitch: Y angle by accelerometer
 * gyroYangle: Y angle by gyroscope
 * compAngleY: Y angle by complementary filter
 * kalAngleY: Y angle by Kalman filter
 */
void loop_mpu6050()
{
	uint32_t now;

#if defined(CHECK_ELAPSED_TIME)
	start_usec = micros();
#endif
	/* Update all the values */
	Wire.beginTransmission(MPU_addr);
	Wire.write(0x3B);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU_addr, 14, true);
	accX = Wire.read()<<8 | Wire.read();
	accY = Wire.read()<<8 | Wire.read();
	accZ = Wire.read()<<8 | Wire.read();
	int16_t tempRaw = Wire.read()<<8 | Wire.read();
	gyroX = Wire.read()<<8 | Wire.read();
	gyroY = Wire.read()<<8 | Wire.read();
	gyroZ = Wire.read()<<8 | Wire.read();
#if defined(CHECK_ELAPSED_TIME)
	elapsed1_usec = micros();
#endif

	now = micros();
	double dt = (double)(now - prev_micros) / 1000000; // Calculate delta time
	prev_micros = now;

	// Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
	// atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
	// It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
	//double roll  = atan2(accY, accZ) * RAD_TO_DEG;
	double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
	//double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
	double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

	//double gyroXrate = gyroX / 131.0; // Convert to deg/s
	double gyroYrate = gyroY / 131.0; // Convert to deg/s

#if defined(CHECK_ELAPSED_TIME)
	elapsed2_usec = micros();
#endif

#ifdef RESTRICT_PITCH
	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
#if 0
	if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
		kalmanX.setAngle(roll);
		compAngleX = roll;
		kalAngleX = roll;
		gyroXangle = roll;
	} else
		kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter

	if (abs(kalAngleX) > 90)
		gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
#endif
	kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
#else
	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
	if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
		kalmanY.setAngle(pitch);
		//compAngleY = pitch;
		kalAngleY = pitch;
		gyroYangle = pitch;
	} else
		kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

#if 0
	if (abs(kalAngleY) > 90)
		gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
	kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif
#endif

#if defined(CHECK_ELAPSED_TIME)
	elapsed3_usec = micros();
#endif

#if 1
	//gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
	gyroYangle += gyroYrate * dt;
#else
	//gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
	//gyroYangle += kalmanY.getRate() * dt;
#endif

	// Reset the gyro angle when it has drifted too much
	if (gyroXangle < -180 || gyroXangle > 180)
		gyroXangle = kalAngleX;
	if (gyroYangle < -180 || gyroYangle > 180)
		gyroYangle = kalAngleY;

	temperature = (double)tempRaw / 340.0 + 36.53;

#if defined(CHECK_ELAPSED_TIME)
	elapsed4_usec = micros();
#endif

}

float get_pitch_angle(void)
{
	return kalAngleY;
}

float get_temperature(void)
{
	return temperature;
}
