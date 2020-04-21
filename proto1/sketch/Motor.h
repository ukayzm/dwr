#ifndef __MOTOR_H__
#define __MOTOR_H__


#include <inttypes.h>


class Motor
{
public:
	virtual void setRpm(int16_t rpm);
	virtual int16_t getRpm(void);
	virtual void loop(uint32_t cur_msec);
	int16_t nCurRpm;
};


#endif // __MOTOR_H__
