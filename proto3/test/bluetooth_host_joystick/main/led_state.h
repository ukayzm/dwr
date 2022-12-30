#ifndef _LED_STATE_H_
#define _LED_STATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BLINK_GPIO 2

typedef enum {
	PAIRING_STATE_NONE,
	PAIRING_STATE_SCANNING,
	PAIRING_STATE_CONNECTING,
	PAIRING_STATE_CONNECTED,
} PAIRING_STATE;

void set_pairing_led_state(PAIRING_STATE new_state);
void setup_led_state(void);

#ifdef __cplusplus
}
#endif

#endif
