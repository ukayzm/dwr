#include "Arduino.h"
#include "dcmotor.h"
#include "pid.h"


DcMotor::DcMotor(int _id, int16_t max_rpm, int pin_pwm, int pin_dirA, int pin_dirB)
{
	id = _id;
	pinPwm = pin_pwm;
	pinDirA = pin_dirA;
	pinDirB = pin_dirB;
	pinMode(pinPwm, OUTPUT);
	pinMode(pinDirA, OUTPUT);
	pinMode(pinDirB, OUTPUT);
	maxRpm = max_rpm;
	curPwm = 0;
	tgtRpm = 0;
}

void DcMotor::attachEncoder(Encoder *encoder)
{
	pEncoder = encoder;
    pEncoder->resetCount();
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

void DcMotor::attachPid(Pid *_pid)
{
	pid = _pid;
}

int16_t DcMotor::getPwm(void)
{
	return curPwm;
}

void DcMotor::setRpm(int16_t rpm)
{
	Motor::setRpm(rpm);
	if (pEncoder == NULL) {
		curRpm = rpm;
	}
	if (pid == NULL) {
		setPwm((long)rpm * 255 / maxRpm);
	}
}

void DcMotor::incRpmPercent(int percent_point)
{
	Motor::incRpmPercent(percent_point);
	DcMotor::setRpm(tgtRpm);
}

void DcMotor::loop(void)
{
	unsigned long cur_usec = micros();
	prevRpm = curRpm;
    if (pEncoder) {
		pEncoder->getCountAndReset(cur_usec);
		curRpm = pEncoder->getCurRpm();
    }
	if (pid) {
		setPwmByPid();
	}
}

void DcMotor::setPwmByPid(void)
{
	int pwm = pid->compute(curRpm, tgtRpm);
	setPwm(pwm);
}

void DcMotor::incKp(float delta)
{
	if (pid) {
		pid->incKp(delta);
	}
}

void DcMotor::incKi(float delta)
{
	if (pid) {
		pid->incKi(delta);
	}
}

void DcMotor::incKd(float delta)
{
	if (pid) {
		pid->incKd(delta);
	}
}

void DcMotor::printStatus(void)
{
	Serial.print(F("\t"));
	Serial.print(curPwm);
	Serial.print(F("\t"));
	Serial.print(curRpm);
	Serial.print(F("\t"));
	Serial.print(tgtRpm);
}
