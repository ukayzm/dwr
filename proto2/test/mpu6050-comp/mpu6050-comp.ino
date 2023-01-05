#include "mpu6050.h"


#define LOOP_USEC 2000


void setup() 
{                
	Serial.begin(115200);
	Serial.println("start setup...");

	setup_mpu6050();

	Serial.println("start loop...");
}

unsigned long loop_end_usec;

void loop() 
{
	unsigned long loop_start_usec = micros();
	float angle1, angle2;

	loop_mpu6050();

#if defined(CHECK_ELAPSED_TIME)
	unsigned long mpu6050_elapsed_usec = micros() - loop_start_usec;
	Serial.print(loop_start_usec);
	Serial.print(": ");
	Serial.print(elapsed1_usec - start_usec);
	Serial.print(" + ");
	Serial.print(elapsed2_usec - elapsed1_usec);
	Serial.print(" + ");
	Serial.print(elapsed3_usec - elapsed2_usec);
	Serial.print(" + ");
	Serial.print(elapsed4_usec - elapsed3_usec);
	Serial.print(" = ");
	Serial.print(mpu6050_elapsed_usec);
	Serial.print(" usec, ");
#endif

	angle1 = get_pitch_angle();
	Serial.print(angle1);

	float temp = get_temperature();
#if 0
	Serial.print(", ");
	Serial.print(temp);
#endif

	/* delay until LOOP_USEC passes */
	unsigned long loop_elapsed_usec = micros() - loop_start_usec;
	if (loop_elapsed_usec < LOOP_USEC) {
		delayMicroseconds(LOOP_USEC - loop_elapsed_usec);
	} else {
		Serial.print(" ! ");
		Serial.print(loop_elapsed_usec);
		Serial.print(" > ");
		Serial.print(LOOP_USEC);
		Serial.print(" us");
	}

	unsigned long loop_to_loop_usec = loop_start_usec - loop_end_usec;
	if (loop_to_loop_usec > 12) 
	{
		Serial.print(", !! ");
		Serial.print(loop_to_loop_usec);
		Serial.print(" us");
	}

	Serial.println();
	loop_end_usec = micros();
}

