#ifndef __TEST_MOTOR_H__
#define __TEST_MOTOR_H__


#include "motor.h"


extern void test_loop(void);
extern void start_test_motor_dir(DcMotor *motor);
extern void start_test_motor_pwm(DcMotor *motor);
extern void start_test_motor_rpm(DcMotor *motor);
extern void start_test_motor_rpm_single(DcMotor *motor);
extern void start_test_mpu6050();


#endif // __TEST_MOTOR_H__
