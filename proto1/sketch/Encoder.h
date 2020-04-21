#ifndef __ENCODER_H__
#define __ENCODER_H__


#include <inttypes.h>


#define NUM_ENCODER		2


class Encoder
{
public:
	Encoder::Encoder(int pin_intr, int pin_dir);
	int16_t Encoder::getCount(void);
	void Encoder::resetCount(void);
private:
	int id;
};


#endif // __ENCODER_H__
