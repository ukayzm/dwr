#include "mpu6050_dmp6.h"

void setup() {
	Serial.begin(115200);
	while (!Serial);
	Serial.println(F("Test MPU6050 DMP6"));
	setup_mpu6050_dmp6();
}

unsigned long last_usec;

void loop() {
	unsigned long start_usec = micros();
	int ret = loop_mpu6050_dmp6();
	if (ret != 0) {
		return;
	}
	unsigned long cur_usec = micros();
	Serial.print(cur_usec - last_usec);
	Serial.print(F("\t"));
	Serial.print(cur_usec - start_usec);
	Serial.print(F("\typr\t"));
	Serial.print(ypr[0]);
	Serial.print(F("\t"));
	Serial.print(ypr[1]);
	Serial.print(F("\t"));
	Serial.print(ypr[2]);
	Serial.print(F("\teuler\t"));
	Serial.print(euler[0]);
	Serial.print(F("\t"));
	Serial.print(euler[1]);
	Serial.print(F("\t"));
	Serial.print(euler[2]);
	Serial.println();
	last_usec = cur_usec;
}
