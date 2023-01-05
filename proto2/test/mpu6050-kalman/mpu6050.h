#ifndef __MPU6050_H__
#define __MPU6050_H__


#define CHECK_ELAPSED_TIME

#define RESTRICT_PITCH // Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf


extern void setup_mpu6050(void);
extern void loop_mpu6050(void);
extern float get_pitch_angle(void);
float get_temperature(void);

extern double gyroXangle, gyroYangle; // Angle calculate using the gyro only
extern double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter


#if defined(CHECK_ELAPSED_TIME)
extern unsigned long start_usec;
extern unsigned long elapsed1_usec;
extern unsigned long elapsed2_usec;
extern unsigned long elapsed3_usec;
extern unsigned long elapsed4_usec;
#endif


#endif // __MPU6050_H__
