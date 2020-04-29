#ifndef __ENCODER_H__
#define __ENCODER_H__


#include <inttypes.h>


#define NUM_ENCODER		2


class Encoder
{
public:
	Encoder(int pin_intr, int pin_dir, int num_intr);
	int16_t getCountAndReset(void);
	void resetCount(void);
	int16_t getIntrPerRevolution(void);
private:
	uint16_t intrPerRevolution;
	int id;
};


#endif // __ENCODER_H__
