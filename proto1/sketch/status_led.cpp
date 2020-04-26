#include "Arduino.h"
#include "board.h"
#include "status_led.h"


static int state;	// LOW or HIGH
static unsigned long last_change_msec;

static int ledOnOffMsec[MODE_MAX][2] = {
	{100, 900},
};

void setup_status_led() {
	pinMode(STATUS_LED_PIN, OUTPUT);
	state = LOW;
	last_change_msec = 0;
}

void loop_status_led() {
	unsigned long cur_msec = millis();
	if (state == LOW) {
		if (cur_msec - last_change_msec > ledOnOffMsec[mode][1]) {
			state = HIGH;
			digitalWrite(STATUS_LED_PIN, state);
			last_change_msec = cur_msec;
		}
	} else {
		if (cur_msec - last_change_msec > ledOnOffMsec[mode][0]) {
			state = LOW;
			digitalWrite(STATUS_LED_PIN, state);
			last_change_msec = cur_msec;
		}
	}
}

