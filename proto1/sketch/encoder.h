#ifndef __ENCODER_H__
#define __ENCODER_H__


#include <inttypes.h>


#define NUM_ENCODER		2
#define MAX_QUEUE		10


class Encoder
{
public:
	Encoder(int pin_intr, int pin_dir, int num_intr);
	int16_t getCountAndReset(unsigned long usec);
	int16_t getCurRpm();
	void resetCount(void);
private:
	int q_count[MAX_QUEUE];
	unsigned long q_usec[MAX_QUEUE];
	int q_index;
	uint16_t intrPerRevolution;
	int id;
};


#endif // __ENCODER_H__
