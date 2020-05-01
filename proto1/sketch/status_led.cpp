#include "Arduino.h"
#include "dcmotor.h"
#include "board.h"
#include "status_led.h"


#define MAX_PHASE	4

static int phase;
static unsigned long last_change_msec;

static char ledOnOffTime[MODE_MAX][MAX_PHASE] = {
	/* x 100 msec; HIGN in even phase, LOW in odd phase */
	{5, 5},
	{10, 10},
	{1, 9},
	{1, 1, 1, 7},
	{30, 0},
};

void setup_status_led() {
	pinMode(STATUS_LED_PIN, OUTPUT);
	phase = 0;
	digitalWrite(STATUS_LED_PIN, HIGH);
	last_change_msec = millis();
}

void loop_status_led() {
	if (ledOnOffTime[mode][phase] == 0) {
		/* mode might be changed. restart from phase 0 */
		phase = 0;
		digitalWrite(STATUS_LED_PIN, HIGH);
		last_change_msec = cur_msec;
		return;
	}
	if (cur_msec - last_change_msec > ledOnOffTime[mode][phase] * 100) {
		/* go to next phase */
		phase++;
		if (ledOnOffTime[mode][phase] == 0 || phase >= MAX_PHASE) {
			phase = 0;
		}
		if ((phase % 2) == 1) {
			/* LOW in odd phase */
			digitalWrite(STATUS_LED_PIN, LOW);
		} else {
			/* HIGH in even phase */
			digitalWrite(STATUS_LED_PIN, HIGH);
		}
		last_change_msec = cur_msec;
	}
}

void print_motor_rpm(void)
{
	int16_t accel0 = motor0->getAccelRpm();
	int16_t accel1 = motor1->getAccelRpm();
	if (accel0 || accel1) {
		sprintf(strbuf, "@ %d: rpm motor0=%d, motor1=%d", cur_msec, motor0->getCurRpm(), motor1->getCurRpm());
		Serial.println(strbuf);
	}
}
