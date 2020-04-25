#ifndef __STATUS_LED_H__
#define __STATUS_LED_H__


#define HIGH_INTERVAL	500
#define LOW_INTERVAL	500

extern void setup_status_led(void);
extern void loop_status_led(unsigned long cur_msec);


#endif // __STATUS_LED_H__
