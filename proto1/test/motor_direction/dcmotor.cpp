#include "Arduino.h"
#include "dcmotor.h"


DcMotor::DcMotor(int _id, int pin_pwm, int pin_dirA, int pin_dirB)
{
	id = _id;
	pinPwm = pin_pwm;
	pinDirA = pin_dirA;
	pinDirB = pin_dirB;
	pinMode(pinPwm, OUTPUT);
	pinMode(pinDirA, OUTPUT);
	pinMode(pinDirB, OUTPUT);
	curPwm = 0;
}

void DcMotor::setPwm(int16_t pwm)
{
	if (pwm > 255)
		pwm = 255;
	if (pwm < -255)
		pwm = -255;

	/* dumb speed up */
	if (pwm > 0) {
		digitalWrite(pinDirA, LOW);
		digitalWrite(pinDirB, HIGH);
	} else if (pwm < 0) {
		digitalWrite(pinDirB, LOW);
		digitalWrite(pinDirA, HIGH);
	} else {
		digitalWrite(pinDirA, LOW);
		digitalWrite(pinDirB, LOW);
	}
	curPwm = pwm;
	if (pwm < 0) {
		pwm = -pwm;
	}
	analogWrite(pinPwm, pwm);
}

int16_t DcMotor::getPwm(void)
{
	return curPwm;
}

