#include "Arduino.h"
#include "dcmotor.h"
#include "board.h"
#include "mpu6050_dmp6.h"

static DcMotor *motorToTest;
static int step;
static long next_step_msec;

void print_test_status(char id, char target, int16_t value)
{
	Serial.print(F("step "));
	Serial.print(step);
	Serial.print(F("; set motor"));
	Serial.print(id);
	if (target == 0) {
		Serial.print(F(" pwm "));
	} else {
		Serial.print(F(" rpm "));
	}
	Serial.println(value);
}

void test_next_step_none(void)
{
}

void test_next_step_motor_dir(void)
{
	int16_t new_pwm = 0;
	if (step < 4) {
		static char pwm[] = {
			0, 255, 0, -255,
		};
		new_pwm = pwm[step];
	} else {
		step = 0;
		mode = MODE_READY;
	}
	motorToTest->setPwm(new_pwm);
	print_test_status(motorToTest->id, 0, new_pwm);
	if (mode != MODE_READY) {
		next_step_msec = cur_msec + 1000;
		step++;
	}
}

void test_next_step_motor_pwm(void)
{
	int16_t new_pwm = 0;
	if (step <= 10) {
		new_pwm = step * 255 / 10;
	} else if (step <= 30) {
		new_pwm = (20 - step) * 255 / 10;
	} else if (step <= 40) {
		new_pwm = (40 - step) * 255 / 10;
	} else {
		step = 0;
		mode = MODE_READY;
	}
	motorToTest->setPwm(new_pwm);
	print_test_status(motorToTest->id, 0, new_pwm);
	if (mode != MODE_READY) {
		next_step_msec = cur_msec + 1000;
		step++;
	}
}

void test_next_step_motor_rpm(void)
{
	int16_t new_rpm = 0;
	if (step <= 10) {
		new_rpm = step * motorToTest->getMaxRpm() / 10;
	} else if (step <= 30) {
		new_rpm = (20 - step) * motorToTest->getMaxRpm() / 10;
	} else if (step <= 40) {
		new_rpm = (40 - step) * motorToTest->getMaxRpm() / 10;
	} else {
		step = 0;
		mode = MODE_READY;
	}
	motorToTest->setRpm(new_rpm);
	print_test_status(motorToTest->id, 1, new_rpm);
	if (mode != MODE_READY) {
		next_step_msec = cur_msec + 1000;
		step++;
	}
}

void test_next_step_motor_rpm_single(void)
{
	int16_t new_rpm = 0;
	if (step == 0) {
		new_rpm = 60;
	} else {
		step = 0;
		mode = MODE_READY;
	}
	motorToTest->setRpm(new_rpm);
	print_test_status(motorToTest->id, 1, new_rpm);
	if (mode != MODE_READY) {
		next_step_msec = cur_msec + 3000;
		step++;
	}
}

void test_next_step_mpu6050(void)
{
	next_step_msec = cur_msec + 100;
	step++;
	Serial.print(F("ypr\t"));
	Serial.print(ypr[0]);
	print_tab();
	Serial.print(ypr[1]);
	print_tab();
	Serial.print(ypr[2]);
	Serial.print(F("\teuler\t"));
	Serial.print(euler[0]);
	print_tab();
	Serial.print(euler[1]);
	print_tab();
	Serial.println(euler[2]);
}

void (*test_next_step[])(void) = {
	test_next_step_none,
	test_next_step_motor_dir,
	test_next_step_motor_pwm,
	test_next_step_motor_rpm,
	test_next_step_motor_rpm_single,
	test_next_step_mpu6050,
};

void test_loop(void)
{
	if (next_step_msec <= cur_msec) {
		test_next_step[mode]();
	}
}

void start_test_motor_dir(DcMotor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_DIR;
	step = 0;
	next_step_msec = 0;
}

void start_test_motor_pwm(DcMotor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_PWM;
	step = 0;
	next_step_msec = 0;
}

void start_test_motor_rpm(DcMotor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_RPM;
	step = 0;
	next_step_msec = 0;
}

void start_test_motor_rpm_single(DcMotor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_RPM_SINGLE;
	step = 0;
	next_step_msec = 0;
}

void start_test_mpu6050()
{
	if (mode == MODE_READY) {
		mode = MODE_TEST_MPU6050;
		step = 0;
		next_step_msec = 0;
	} else {
		step = 0;
		mode = MODE_READY;
	}
}

