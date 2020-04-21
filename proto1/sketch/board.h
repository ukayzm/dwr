#ifndef __BOARD_H__
#define __BOARD_H__

#include <inttypes.h>


/*
 * ===================
 * PIN configuration
 * ===================
 */

/* motor encoder */
#define PIN_ENCODER_INTR_A		2
#define PIN_ENCODER_INTR_B		3
#define PIN_ENCODER_DIR_A		4
#define PIN_ENCODER_DIR_B		5

/* motor */
#define PIN_PWM_A				9
#define PIN_PWM_B				10
#define PIN_DIR1_MOTOR_A		5
#define PIN_DIR2_MOTOR_A		6
#define PIN_DIR1_MOTOR_B		7
#define PIN_DIR2_MOTOR_B		8

/* Infre Red */
#define IR_PIN			A3


/* loop interval (msec) */
#define LOOP_MS     6
#define INTERVAL_BALANCING	LOOP_MS


extern void setup_board(void);
extern void setDivisorTimer1(int divisor);
extern uint16_t getPwmFrequencyTimer1(void);


#endif // __BOARD_H__
