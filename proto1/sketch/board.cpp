#include "Arduino.h"
#include "board.h"
#include "dcmotor.h"
#include "encoder.h"
#include "pwm.h"
#include "mpu6050_dmp6.h"
#include "status_led.h"
#include "ir.h"
#include "test.h"


DcMotor motor0 = DcMotor(0, MOTOR_MAX_RPM, PIN_PWM_A, PIN_DIR1_MOTOR_A, PIN_DIR2_MOTOR_A);
DcMotor motor1 = DcMotor(1, MOTOR_MAX_RPM, PIN_PWM_B, PIN_DIR1_MOTOR_B, PIN_DIR2_MOTOR_B);
Encoder encoder0 = Encoder(PIN_ENCODER_INTR_A, PIN_ENCODER_DIR_A, ENCODER_INTR_PER_REVOLUTION);
Encoder encoder1 = Encoder(PIN_ENCODER_INTR_B, PIN_ENCODER_DIR_B, ENCODER_INTR_PER_REVOLUTION);
Pid pid0 = Pid(MOTOR_KP, MOTOR_KI, MOTOR_KD);
Pid pid1 = Pid(MOTOR_KP, MOTOR_KI, MOTOR_KD);


unsigned long prev_msec;
unsigned long cur_msec;
unsigned long cur_usec;
Mode mode;


void setup_board()
{
	Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately
	Serial.println(F("Xiaomi Phone Charger 10400"));
	Serial.println(F("USB to 12V converter"));
	Serial.println(F("L298N"));

	setDivisorTimer1(1);

	setup_mpu6050_dmp6();
	setup_status_led();
	setup_ir();

	motor0.attachEncoder(&encoder0);
	//motor0.attachPid(&pid0);

	motor1.attachEncoder(&encoder1);
	//motor0.attachPid(&pid1);

	prev_msec = millis();
	mode = 0;
}

void loop_board()
{
	cur_msec = millis();
	cur_usec = micros();
	if (cur_msec == prev_msec) {
		return;
	}
	prev_msec = cur_msec;

	loop_mpu6050_dmp6();
	motor0.loop();
	motor1.loop();

	loop_ir();
	loop_test();
	loop_status_led();
}

