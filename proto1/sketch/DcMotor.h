#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__


#include <inttypes.h>
#include "Motor.h"
#include "Encoder.h"
#include "pid.h"


class DcMotor : public Motor
{
public:
	DcMotor(int pinPwm, int pinDirA, int pinDirB);
	void setPwm(int16_t pwm);			/* PWM -255 ~ +255 */
	int16_t getPwm(void);
	void attachEncoder(Encoder *encoder);
	void enablePid(double Kp, double Ki, double Kd);
	void setRpm(int16_t rpm);
	int16_t getCurRpm(void);
	void loop(void);
private:
	int nPinPwm, nPinDirA, nPinDirB;
	int16_t nCurPwm;
    int16_t nTgtRpm;
	Encoder *pEncoder;
    Pid *pid;
    double fInRpm, fTgtRpm, fTgtPwm;
    unsigned long prev_usec;
	int16_t getCurRpmFromEncoder(unsigned long cur_usec);
	void setPwmByPid(void);
};


#endif // __DC_MOTOR_H__
