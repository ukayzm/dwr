#include "Arduino.h"
#include "DcMotor.h"


DcMotor::DcMotor(int pinPwm, int pinDirA, int pinDirB)
{
	nPinPwm = pinPwm;
	nPinDirA = pinDirA;
	nPinDirB = pinDirB;
	pinMode(nPinPwm, OUTPUT);
	pinMode(nPinDirA, OUTPUT);
	pinMode(nPinDirB, OUTPUT);

	Serial.print("DcMotor PIN_PWM = ");
	Serial.print(pinPwm);
	Serial.print(", PIN_DIR_A = ");
	Serial.print(pinDirA);
	Serial.print(", PIN_DIR_B = ");
	Serial.print(pinDirB);
	Serial.println();
}

void DcMotor::attachEncoder(Encoder *encoder)
{
	pEncoder = encoder;
}

void DcMotor::setPwm(int16_t pwm)
{
	if (pwm > 255)
		pwm = 255;
	if (pwm < -255)
		pwm = -255;

	/* dumb speed up */
	if (pwm > 0) {
		digitalWrite(nPinDirA, LOW);
		digitalWrite(nPinDirB, HIGH);
	} else if (pwm < 0) {
		digitalWrite(nPinDirB, LOW);
		digitalWrite(nPinDirA, HIGH);
	} else {
		digitalWrite(nPinDirA, LOW);
		digitalWrite(nPinDirB, LOW);
	}
	nCurPwm = pwm;
	if (pwm < 0) {
		pwm = -pwm;
	}
	analogWrite(nPinPwm, pwm);
}

int16_t DcMotor::getPwm(void)
{
	return nCurPwm;
}

void Motor::setRpm(int16_t rpm)
{
	nCurRpm = rpm;
}

int16_t Motor::getRpm(void)
{
	return nCurRpm;
}

void Motor::loop(uint32_t cur_msec)
{
}
