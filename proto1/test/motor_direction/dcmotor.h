#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__


#include <inttypes.h>
#include "motor.h"


class DcMotor : public Motor
{
public:
	DcMotor(int _id, int pin_pwm, int pin_dirA, int pin_dirB);
	void setPwm(int16_t pwm);			/* PWM -255 ~ +255 */
	int16_t getPwm(void);
private:
	char pinPwm, pinDirA, pinDirB;
	int16_t curPwm;
};


#endif // __DC_MOTOR_H__
