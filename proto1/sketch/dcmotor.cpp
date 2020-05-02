#include "Arduino.h"
#include "dcmotor.h"
#include "pid.h"
#include "board.h"


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
	tgtRpm = rpm;
}

void DcMotor::loop(void)
{
	unsigned long cur_usec = micros();
	prevRpm = curRpm;
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
	print_tab();
	Serial.print(curPwm);
	print_tab();
	Serial.print(curRpm);
}
