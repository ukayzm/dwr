#include "Arduino.h"
#include "dcmotor.h"
#include "pid.h"


DcMotor::DcMotor(int pinPwm, int pinDirA, int pinDirB, int16_t max_rpm)
{
	nPinPwm = pinPwm;
	nPinDirA = pinDirA;
	nPinDirB = pinDirB;
	pinMode(nPinPwm, OUTPUT);
	pinMode(nPinDirA, OUTPUT);
	pinMode(nPinDirB, OUTPUT);
	maxRpm = max_rpm;

	Serial.print("DcMotor PIN_PWM = ");
	Serial.print(pinPwm);
	Serial.print(", PIN_DIR_A = ");
	Serial.print(pinDirA);
	Serial.print(", PIN_DIR_B = ");
	Serial.print(pinDirB);
	Serial.print(", maxRpm = ");
	Serial.print(maxRpm);
	Serial.println();
}

void DcMotor::attachEncoder(Encoder *encoder)
{
	pEncoder = encoder;
    pEncoder->resetCount();
    prev_usec = micros();
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

void DcMotor::enablePid(double Kp, double Ki, double Kd)
{
	pid = new Pid(Kp, Ki, Kd);
}

int16_t DcMotor::getPwm(void)
{
	return nCurPwm;
}

void DcMotor::setRpm(int16_t rpm)
{
	nTgtRpm = rpm;
}

void DcMotor::loop(void)
{
	unsigned long cur_usec = micros();
    if (pEncoder) {
		curRpm = getCurRpmFromEncoder(cur_usec);
    }
	if (pid) {
		setPwmByPid();
	}
	prev_usec = cur_usec;
}

int16_t DcMotor::getCurRpmFromEncoder(unsigned long cur_usec)
{
    int16_t count = pEncoder->getCountAndReset();
	int dt = cur_usec - prev_usec;
	if (dt <= 0) {
		return curRpm;
	}
	return (double)(count * 60) / pEncoder->getIntrPerRevolution() * 1000000 / dt;
}

void DcMotor::setPwmByPid(void)
{
	int pwm = pid->compute(curRpm, nTgtRpm);
	setPwm(pwm);
}

