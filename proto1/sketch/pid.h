#ifndef __PID_H__
#define __PID_H__


class Pid
{
public:
	Pid(float kp, float ki, float kd);
	void SetOutputLimits(float min, float max);
	void reset(float curInput, float curOutput);
	float compute(float input, float setpoint);
	void incKp(float delta);
	void incKi(float delta);
	void incKd(float delta);
	float getKp();
	float getKi();
	float getKd();
private:
	float Kp;
	float Ki;
	float Kd;
	float iTerm;
	float lastInput;
	float outMin;
	float outMax;
	unsigned long last_usec;
};


#endif // __PID_H__
