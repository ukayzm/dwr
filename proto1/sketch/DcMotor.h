#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__


#include <inttypes.h>
#include "Motor.h"
#include "Encoder.h"


class DcMotor : Motor
{
public:
	DcMotor(int pinPwm, int pinDirA, int pinDirB);
	void setPwm(int16_t pwm);			/* PWM -255 ~ +255 */
	int16_t getPwm(void);
	void attachEncoder(Encoder *encoder);
private:
	int nPinPwm, nPinDirA, nPinDirB;
	int16_t nCurPwm;
	Encoder *pEncoder;
};

#endif // __DC_MOTOR_H__
