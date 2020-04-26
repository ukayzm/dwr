#include "Arduino.h"
#include "board.h"
#include "DcMotor.h"
#include "Encoder.h"
#include "pwm.h"
#include "mpu6050_dmp6.h"
#include "status_led.h"
#include "ir.h"


DcMotor motorLeft(PIN_PWM_A, PIN_DIR1_MOTOR_A, PIN_DIR2_MOTOR_A);
DcMotor motorRight(PIN_PWM_B, PIN_DIR1_MOTOR_B, PIN_DIR2_MOTOR_B);
Encoder encoderLeft(PIN_ENCODER_INTR_A, PIN_ENCODER_DIR_A, ENCODER_INTR_PER_REVOLUTION);
Encoder encoderRight(PIN_ENCODER_INTR_B, PIN_ENCODER_DIR_B, ENCODER_INTR_PER_REVOLUTION);


unsigned long prev_msec;
Mode mode;

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

	motorLeft.attachEncoder(&encoderLeft);
	motorLeft.enablePid(MOTOR_KP, MOTOR_KI, MOTOR_KD);
	motorRight.attachEncoder(&encoderRight);
	motorRight.enablePid(MOTOR_KP, MOTOR_KI, MOTOR_KD);

	prev_msec = millis();
	mode = 0;
}

void loop_board()
{
	unsigned long cur_msec = millis();
	unsigned long cur_usec = micros();
	if (cur_msec == prev_msec) {
		return;
	}
	prev_msec = cur_msec;

	//loop_mpu6050_dmp6(cur_msec);
	loop_status_led();
	//loop_ir();
}

