#ifndef __PWM_H__
#define __PWM_H__


/*
 * For PIN 9 and 10, the frequency for the divisors are:
 * o 31250 Hz for 1
 * o  3906 Hz for 8
 * o   488 Hz for 64
 * o   122 Hz for 256
 * o    30 Hz for 1024
 */
extern void setDivisorTimer1(int divisor);
extern uint16_t getPwmFrequencyTimer1(void);


#endif // __PWM_H__
