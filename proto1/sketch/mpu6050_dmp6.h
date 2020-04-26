#ifndef __MPU6050_DMP6_H__
#define __MPU6050_DMP6_H__


extern void setup_mpu6050_dmp6(void);
extern int loop_mpu6050_dmp6(uint32_t cur_usec);
extern float euler[3];         // [psi, theta, phi]    Euler angle container
extern float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


// uncomment "OUTPUT_READABLE_EULER" if you want to see Euler angles
// (in degrees) calculated from the quaternions coming from the FIFO.
// Note that Euler angles suffer from gimbal lock (for more info, see
// http://en.wikipedia.org/wiki/Gimbal_lock)
//#define OUTPUT_READABLE_EULER

// uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
// pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.
// Also note that yaw/pitch/roll angles suffer from gimbal lock (for
// more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
//#define OUTPUT_READABLE_YAWPITCHROLL


#endif // __MPU6050_DMP6_H__

