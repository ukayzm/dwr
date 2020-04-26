#include "Arduino.h"
#include "pid.h"


Pid::Pid(float kp, float ki, float kd)
{
	Kp = kp;
	Ki = ki;
	Kd = kd;
	outMin = 0;
	outMax = 0;
	reset(0, 0);
}

void Pid::reset(float curInput, float curOutput)
{
	last_usec = micros();
	lastInput = curInput;
	iTerm = curOutput;
	if (outMin != 0 || outMax != 0) {
		if (iTerm < outMin) {
			iTerm = outMin;
		} else if (iTerm > outMax) {
			iTerm = outMax;
		}
	}
}

void Pid::SetOutputLimits(float min, float max)
{
	outMin = min;
	outMax = max;
}

float Pid::compute(float input, float setpoint)
{
	unsigned long cur_usec = micros();
	float dt = (float)(cur_usec - last_usec);
	if (dt <= 0) {
		return iTerm;
	}
	float error = setpoint - input;

	/* compute pTerm */
	float pTerm = Kp * error;

	/* compute iTerm */
	iTerm += Ki * error;
	if (outMin != 0 || outMax != 0) {
		if (iTerm < outMin) {
			iTerm = outMin;
		} else if (iTerm > outMax) {
			iTerm = outMax;
		}
	}

	/* compute dTerm */
	float dInput = input - lastInput;
	float dTerm = Kd * (-dInput / dt);

	/* compute output */
	float output = pTerm + iTerm + dTerm;
	if (outMin != 0 || outMax != 0) {
		if (output < outMin) {
			output = outMin;
		} else if (output > outMax) {
			output = outMax;
		}
	}

	/* remember some variables for next time */
	lastInput = input;
	last_usec = cur_usec;

	return output;
}


void Pid::incKp(float delta)
{
	Kp += delta;
}

void Pid::incKi(float delta)
{
	Ki += delta;
}

void Pid::incKd(float delta)
{
	Kd += delta;
}

float Pid::getKp(void)
{
	return Kp;
}

float Pid::getKi(void)
{
	return Ki;
}

float Pid::getKd(void)
{
	return Kd;
}

