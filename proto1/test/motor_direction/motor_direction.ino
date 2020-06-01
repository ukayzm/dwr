#include "dcmotor.h"


#define PIN_PWM_A				9
#define PIN_PWM_B				10
#define PIN_DIR1_MOTOR_A		6
#define PIN_DIR2_MOTOR_A		5
#define PIN_DIR1_MOTOR_B		7
#define PIN_DIR2_MOTOR_B		8


DcMotor motor0 = DcMotor(0, PIN_PWM_A, PIN_DIR1_MOTOR_A, PIN_DIR2_MOTOR_A);
DcMotor motor1 = DcMotor(1, PIN_PWM_B, PIN_DIR1_MOTOR_B, PIN_DIR2_MOTOR_B);


void setup() {
	Serial.begin(115200);
}

void loop() {
	Serial.println(F("Forward for 1000 msec"));
	motor0.setPwm(255);
	motor1.setPwm(255);
	delay(1000);
	Serial.println(F("pause for 1000 msec"));
	motor0.setPwm(0);
	motor1.setPwm(0);
	delay(1000);
	Serial.println(F("Backward for 1000 msec"));
	motor0.setPwm(-255);
	motor1.setPwm(-255);
	delay(1000);
	Serial.println(F("Stop for 3000 msec"));
	motor0.setPwm(0);
	motor1.setPwm(0);
	delay(3000);
}
