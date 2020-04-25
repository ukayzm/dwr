#include "Arduino.h"
#include "status_led.h"


static int state;	// LOW or HIGH
static unsigned long last_change_msec;


void setup_status_led() {
	pinMode(LED_BUILTIN, OUTPUT);
	state = LOW;
	last_change_msec = 0;
}

void loop_status_led(unsigned long cur_msec) {
	if (state == LOW) {
		if (cur_msec - last_change_msec > LOW_INTERVAL) {
			state = HIGH;
			digitalWrite(LED_BUILTIN, state);
			last_change_msec = cur_msec;
		}
	} else {
		if (cur_msec - last_change_msec > HIGH_INTERVAL) {
			state = LOW;
			digitalWrite(LED_BUILTIN, state);
			last_change_msec = cur_msec;
		}
	}
}

