#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__

#include <inttypes.h>

extern int16_t count_m0, count_m1;
extern unsigned long total_count_m0, total_count_m1;

extern void init_motors(void);

#define INTR_PER_REV	(12 * 34)	/* interrupt count per motor revolution */

/* the initial PWM value to start wheel spinning */
#define INITIAL_PWM_M0	 40
#define INITIAL_PWM_M1	 42

/* the minimum PWM value to keep wheel spinning */
#define MIN_PWM_M0	 5
#define MIN_PWM_M1	 5

/* speed (mm/sec) at the minimum PWM */
#define MIN_RPM_M0	42
#define MIN_RPM_M1	42

#define NUM_INTR_SAVE	3

class DcMotor
{
private:
	int16_t enc_count;
	int pin_pwm, pin_ctrl0, pin_ctrl1, pin_cs;
	int pin_intr, pin_dir;
	unsigned long ulLastUpdateUs;
	int16_t enc_count_buf[NUM_INTR_SAVE];
	int enc_count_index;
	unsigned long enc_interval_buf[NUM_INTR_SAVE];
	unsigned long ulIntervalUs;
	unsigned long ulTotalIntr;
	int16_t nCurPwm;
	int16_t nCurRpm;	/* current speed in mm per second */
	void setMotorDir(int16_t pwm);
	void setMotorPwm(int16_t pwm);
	int calibratePwmAtLowSpeed(int pwm);

public:
	DcMotor();
	void SetEncoderPin(int intr_pin, int dir_pin);
	void SetPin(int pwm_pin, int ctrl0_pin, int ctrl1_pin, int cs_pin);
	void SetPwm(int16_t pwm);			/* PWM -255 ~ +255 */
	void UpdateRpm(void);
	void Print(void);
	int16_t GetCurPwm(void);
	int16_t GetCurRpm(void);
	uint16_t GetCurrent(void);
};

#endif // __DC_MOTOR_H__
