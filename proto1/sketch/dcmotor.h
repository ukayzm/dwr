#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__


#include <inttypes.h>
#include "motor.h"
#include "encoder.h"
#include "pid.h"


class DcMotor : public Motor
{
public:
	DcMotor(int _id, int pin_pwm, int pin_dirA, int pin_dirB, int16_t max_rpm);
	void setPwm(int16_t pwm);			/* PWM -255 ~ +255 */
	int16_t getPwm(void);
	void attachEncoder(Encoder *encoder);
	void attachPid(Pid *_pid);
	void setRpm(int16_t rpm);
	void loop(void);
	void incKp(float delta);
	void incKi(float delta);
	void incKd(float delta);
	void printStatus(void);
	void incRpmPercent(int percent_point);
private:
	char pinPwm, pinDirA, pinDirB;
	int16_t curPwm;
	Encoder *pEncoder;
    Pid *pid;
    double fInRpm, fTgtRpm, fTgtPwm;
	int16_t getCurRpmFromEncoder(unsigned long cur_usec);
	void setPwmByPid(void);
};


#endif // __DC_MOTOR_H__
