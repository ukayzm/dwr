#include "Arduino.h"
#include "dcmotor.h"
#include "board.h"
#include "mpu6050_dmp6.h"

static DcMotor *motorToTest;
static int step;
static long next_step_msec;

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
	sprintf(strbuf, "step %d; set motor%d pwm %d", step, motorToTest->id, new_pwm);
	Serial.println(strbuf);
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
	sprintf(strbuf, "step %d; set motor%d pwm %d", step, motorToTest->id, new_pwm);
	Serial.println(strbuf);
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
	sprintf(strbuf, "step %d; set motor%d rpm %d", step, motorToTest->id, new_rpm);
	Serial.println(strbuf);
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
	sprintf(strbuf, "step %d; set motor%d rpm %d", step, motorToTest->id, new_rpm);
	Serial.println(strbuf);
	if (mode != MODE_READY) {
		next_step_msec = cur_msec + 3000;
		step++;
	}
}

void test_next_step_mpu6050(void)
{
	next_step_msec = cur_msec + 100;
	step++;
	sprintf(strbuf, "ypr\t%d\t%d\t%d\teuler\t%d\t%d\t%d", ypr[0], ypr[1], ypr[2], euler[0], euler[1], euler[2]);
	Serial.println(strbuf);
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
	Serial.print(__func__);
	Serial.print(" motor");
	Serial.println(motor->id);
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_DIR;
	step = 0;
	next_step_msec = 0;
}

void start_test_motor_pwm(DcMotor *motor)
{
	Serial.print(__func__);
	Serial.print(" motor");
	Serial.println(motor->id);
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_PWM;
	step = 0;
	next_step_msec = 0;
}

void start_test_motor_rpm(DcMotor *motor)
{
	Serial.print(__func__);
	Serial.print(" motor");
	Serial.println(motor->id);
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_RPM;
	step = 0;
	next_step_msec = 0;
}

void start_test_motor_rpm_single(DcMotor *motor)
{
	Serial.print(__func__);
	Serial.print(" motor");
	Serial.println(motor->id);
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_RPM_SINGLE;
	step = 0;
	next_step_msec = 0;
}

void start_test_mpu6050()
{
	if (mode == MODE_READY) {
		Serial.println(__func__);
		mode = MODE_TEST_MPU6050;
		step = 0;
		next_step_msec = 0;
	} else {
		Serial.println("stop testing");
		step = 0;
		mode = MODE_READY;
	}
}

