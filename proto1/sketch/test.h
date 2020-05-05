#ifndef __TEST_H__
#define __TEST_H__


#include "motor.h"


extern void loop_test(void);
extern void start_test_motor_dir(DcMotor *motor);
extern void start_test_motor_pwm(DcMotor *motor);
extern void start_test_motor_rpm(DcMotor *motor);
extern void start_test_encoder();
extern void start_test_mpu6050();


#endif // __TEST_H__
