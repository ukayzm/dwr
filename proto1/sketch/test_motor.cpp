#include "Arduino.h"
#include "motor.h"
#include "board.h"

static Motor *motorToTest;
static int step;
static long next_step_msec;

void test_next_step_none(void)
{
}

void test_next_step_motor_dir(void)
{
	if (step < 4) {
		static char rpm[] = {
			0, 60, 0, -60,
		};
		motorToTest->setRpm(rpm[step]);
		if (step % 2 == 0) {
			next_step_msec = cur_msec + 500;
		} else {
			next_step_msec = cur_msec + 1000;
		}
		step++;
	} else {
		step = 0;
		mode = MODE_READY;
	}
}

void test_next_step_motor_speed(void)
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
	next_step_msec = cur_msec + 1000;
	step++;
}

void (*test_next_step[])(void) = {
	test_next_step_none,
	test_next_step_motor_dir,
	test_next_step_motor_speed,
};

void test_loop(void)
{
	if (next_step_msec <= cur_msec) {
		test_next_step[mode]();
	}
}

void start_test_motor_dir(Motor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_DIR;
	step = 0;
	next_step_msec = 0;
}

void start_test_motor_speed(Motor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_SPEED;
	step = 0;
	next_step_msec = 0;
}

