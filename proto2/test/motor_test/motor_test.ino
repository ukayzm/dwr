/*
 * prj3.1 - a4988
 */
#include "board.h"

extern void motor_set_rpm(int16_t rpm);

void setup() 
{                
	Serial.begin(115200);

	setup_board();
}

#define MAX_RPM 200
#define STEP	1
#define DELAY	50

void loop() 
{
	int i;

	for (i = 0; i < MAX_RPM; i += STEP) {
		motor_set_rpm(i);
		delay(DELAY);
	}
	for (i = MAX_RPM; i >= -MAX_RPM; i -= STEP) {
		motor_set_rpm(i);
		delay(DELAY);
	}
	for (i = -MAX_RPM; i < 0; i += STEP) {
		motor_set_rpm(i);
		delay(DELAY);
	}
}
