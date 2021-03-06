#ifndef __BOARD_H__
#define __BOARD_H__

#include <inttypes.h>
#include "dcmotor.h"


/*
 * ===================
 * PIN configuration
 * ===================
 */

/* motor encoder */
#define PIN_ENCODER_INTR_A		2
#define PIN_ENCODER_INTR_B		3
#define PIN_ENCODER_DIR_A		4
#define PIN_ENCODER_DIR_B		11

#define ENCODER_INTR_PER_REVOLUTION		657		/* 657 intr per revolution */


/* motor */
#define PIN_PWM_A				9
#define PIN_PWM_B				10
#define PIN_DIR1_MOTOR_A		6
#define PIN_DIR2_MOTOR_A		5
#define PIN_DIR1_MOTOR_B		7
#define PIN_DIR2_MOTOR_B		8

#define MOTOR_MAX_RPM			107

#define MOTOR_KP				10
#define MOTOR_KI				1
#define MOTOR_KD				1


/* Infre Red */
#define IR_PIN			A3


/* status LED */
#define STATUS_LED_PIN			LED_BUILTIN


/* loop interval (msec) */
#define LOOP_USEC     2000


/* operation mode */
enum Mode {
	MODE_READY,
	MODE_TEST_MOTOR_DIR,
	MODE_TEST_MOTOR_PWM,
	MODE_TEST_MOTOR_RPM,
	MODE_TEST_ENCODER,
	MODE_TEST_MPU6050,
	MODE_MAX,
};
extern Mode mode;

extern unsigned long cur_msec;
extern unsigned long cur_usec;


extern DcMotor motor0, motor1;


extern void setup_board(void);
extern void loop_board(void);


#endif // __BOARD_H__
