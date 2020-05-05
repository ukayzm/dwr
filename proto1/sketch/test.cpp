#include "Arduino.h"
#include "dcmotor.h"
#include "board.h"
#include "mpu6050_dmp6.h"

static DcMotor *motorToTest;
static int step;
static long next_step_msec;
extern uint32_t ulTotalCount[NUM_ENCODER];

void print_tab(void)
{
	Serial.print(F("\t"));
}

void print_test_status(int id, char target, int16_t value)
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

void start_test_motor_dir(DcMotor *motor)
{
	if (mode == MODE_READY) {
		motorToTest = motor;
		mode = MODE_TEST_MOTOR_DIR;
		step = 0;
		next_step_msec = 0;
	} else {
		step = 0;
		mode = MODE_READY;
		motor->setPwm(0);
		print_test_status(motor->id, 0, 0);
	}
}

void test_next_step_motor_dir(void)
{
	int16_t new_pwm = 0;
	static int16_t pwm[] = {
		0, 255, 0, -255,
	};
	new_pwm = pwm[step%4];
	motorToTest->setPwm(new_pwm);
	print_test_status(motorToTest->id, 0, new_pwm);
	if (mode != MODE_READY) {
		step++;
		next_step_msec = cur_msec + 1000;
	}
}

void start_test_motor_pwm(DcMotor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_PWM;
	step = 0;
	next_step_msec = 0;
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

void start_test_motor_rpm(DcMotor *motor)
{
	motorToTest = motor;
	mode = MODE_TEST_MOTOR_RPM;
	step = 0;
	next_step_msec = 0;
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

void start_test_encoder()
{
	if (mode == MODE_READY) {
		mode = MODE_TEST_ENCODER;
		step = 0;
		next_step_msec = 0;
	} else {
		step = 0;
		mode = MODE_READY;
		motor0.setPwm(0);
		motor1.setPwm(0);
	}
}

void test_next_step_encoder(void)
{
	static uint32_t count0, count1;
	int16_t new_rpm = 0;
	if (step == 0) {
		new_rpm = 255;
		next_step_msec = cur_msec + 1000;
		step++;
	} else if (step == 1) {
		new_rpm = 255;
		count0 = ulTotalCount[0];
		count1 = ulTotalCount[1];
		next_step_msec = cur_msec + 60000;
		step++;
	} else {
		uint32_t count_intr0 = ulTotalCount[0] - count0;
		uint32_t count_intr1 = ulTotalCount[1] - count1;
		step = 0;
		mode = MODE_READY;
		Serial.print("motor0:\t");
		Serial.print(count_intr0);
		Serial.print(" intr\t");
		Serial.print((float)count_intr0 / 60);
		Serial.print(" intr/s\t");
		Serial.print((float)count_intr0 / ENCODER_INTR_PER_REVOLUTION);
		Serial.print(" rpm,\tmotor1:\t");
		Serial.print(count_intr1);
		Serial.print(" intr\t");
		Serial.print((float)count_intr1 / 60);
		Serial.print(" intr/s\t");
		Serial.print((float)count_intr1 / ENCODER_INTR_PER_REVOLUTION);
		Serial.println(" rpm");
	}
	motor0.setRpm(new_rpm);
	motor1.setRpm(new_rpm);
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
	test_next_step_encoder,
	test_next_step_mpu6050,
};

void loop_test(void)
{
	if (mode != MODE_READY) {
		if (next_step_msec <= cur_msec) {
			test_next_step[mode]();
		}
	}

	int16_t accel0 = motor0.getAccelRpm();
	int16_t accel1 = motor1.getAccelRpm();
	if (accel0 || accel1) {
		Serial.print(cur_msec);
		motor0.printStatus();
		motor1.printStatus();
		if (motor0.getPwm() == 0 && motor1.getPwm() == 0) {
			Serial.print(F("\t"));
			Serial.print(ulTotalCount[0]);
			Serial.print(F("\t"));
			Serial.print(ulTotalCount[1]);
		}
		Serial.println();
	}
}

