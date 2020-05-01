#ifndef __MOTOR_H__
#define __MOTOR_H__


#include <inttypes.h>


class Motor
{
public:
	virtual void setRpm(int16_t rpm);
	int16_t getAccelRpm(void) {
		return curRpm - prevRpm;
	}
	int16_t getCurRpm(void) {
		return curRpm;
	}
	int16_t getMaxRpm(void) {
		return maxRpm;
	}
	virtual void loop(void);
	int id;
protected:
	int16_t maxRpm;
	int16_t prevRpm, curRpm;
};


#endif // __MOTOR_H__
