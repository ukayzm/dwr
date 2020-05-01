#include "Arduino.h"
#include "board.h"
#include "dcmotor.h"
#include "encoder.h"
#include "pwm.h"
#include "mpu6050_dmp6.h"
#include "status_led.h"
#include "ir.h"
#include "test_motor.h"


DcMotor *motor0, *motor1;


unsigned long prev_msec;
unsigned long cur_msec;
unsigned long cur_usec;
Mode mode;

char strbuf[256];


void setup_board()
{
	Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately
	Serial.println("Power supply: Xiaomi Phone Charger 10400 to 12V converter USB type");
	Serial.println("Motor driver: L298N");

	setDivisorTimer1(1);

	setup_mpu6050_dmp6();
	setup_status_led();
	setup_ir();

	motor0 = new DcMotor(0, 300, PIN_PWM_A, PIN_DIR1_MOTOR_A, PIN_DIR2_MOTOR_A);
	motor0->attachEncoder(new Encoder(PIN_ENCODER_INTR_A, PIN_ENCODER_DIR_A, ENCODER_INTR_PER_REVOLUTION));
	motor0->enablePid(MOTOR_KP, MOTOR_KI, MOTOR_KD);

	motor1 = new DcMotor(1, 300, PIN_PWM_B, PIN_DIR1_MOTOR_B, PIN_DIR2_MOTOR_B);
	motor1->attachEncoder(new Encoder(PIN_ENCODER_INTR_B, PIN_ENCODER_DIR_B, ENCODER_INTR_PER_REVOLUTION));
	motor1->enablePid(MOTOR_KP, MOTOR_KI, MOTOR_KD);

	prev_msec = millis();
	mode = 0;
}

int first = 0;
void loop_board()
{
	cur_msec = millis();
	cur_usec = micros();
	if (cur_msec == prev_msec) {
		return;
	}
	prev_msec = cur_msec;

	loop_mpu6050_dmp6();
	loop_ir();
	if (mode != MODE_READY) {
		test_loop();
	}

	motor0->loop();
	motor1->loop();
	loop_status_led();
	if (mode != MODE_READY) {
		print_motor_rpm();
	}
}

