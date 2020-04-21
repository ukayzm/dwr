#include "Arduino.h"
#include "board.h"
#include "DcMotor.h"
#include "Encoder.h"
#include "pwm.h"
#include "mpu6050.h"


DcMotor motorLeft(PIN_PWM_A, PIN_DIR1_MOTOR_A, PIN_DIR2_MOTOR_A);
DcMotor motorRight(PIN_PWM_B, PIN_DIR1_MOTOR_B, PIN_DIR2_MOTOR_B);
Encoder encoderLeft(PIN_ENCODER_INTR_A, PIN_ENCODER_DIR_A);
Encoder encoderRight(PIN_ENCODER_INTR_B, PIN_ENCODER_DIR_B);

unsigned long loop_start_usec;

void setup_board()
{
	Serial.println("Power supply: Xiaomi Phone Charger 10400 to 12V converter USB type");
	Serial.println("Motor driver: L298N");

	/*
	 * For M0_PWM_PIN 9 and M1_PWM_PIN 10, the frequency for the divisors are:
	 * o 31250 Hz for 1
	 * o  3906 Hz for 8
	 * o   488 Hz for 64
	 * o   122 Hz for 256
	 * o    30 Hz for 1024
	 */
	setDivisorTimer1(1);

	mpu6050_setup();

	loop_start_usec = micros();
}

void loop_board()
{
	mpu6050_loop();

	/* delay until LOOP_USEC passes */
	unsigned long used_usec = micros() - loop_start_usec;
	if (used_usec < LOOP_USEC) {
		delayMicroseconds(LOOP_USEC - used_usec);
	}
	loop_start_usec = micros();
}

