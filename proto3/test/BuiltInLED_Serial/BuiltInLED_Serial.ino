/*
  ESP 32 Blink
  Turns on an LED on for a half second, then off for a half second, repeatedly.
  The ESP32 has an internal blue LED at D2 (GPIO 02)
*/

int LED_BUILTIN = 2;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(115200);
	while (!Serial);
	Serial.println(F("Test Serial"));
}

void test_serial() {
	static int i = 0;

	Serial.println();
	Serial.print(F("115200, i = "));
	Serial.println(i++);

	unsigned long start_usec, cur_usec;
	// unsigned long usec1, usec2, usec3, usec4, usec5, usec6, usec7, usec8, usec9;

	start_usec = micros();
	Serial.print(F("1"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(1 character): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("1234567890"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(10 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("123456789012"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(12 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.println(F("1234567890"));
	cur_usec = micros();
	Serial.print(F("\tSerial.println(10 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("1234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(40 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.println(F("1234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.print(F("\tSerial.println(40 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.println(F("1234567890123456789012345678901234567890"));
	Serial.println(F("1234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.print(F("\tSerial.println(40 characters) x 2: "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("12345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(80 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.println(F("12345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.print(F("\tSerial.println(80 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.println(F("12345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	Serial.println(F("12345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.print(F("\tSerial.println(80 characters) x 2: "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(90 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(100 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(110 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.println();
	Serial.print(F("\tSerial.print(120 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.println(F("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.print(F("\tSerial.println(120 characters): "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");
}

void loop() {
	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(500);                        // wait for a half second
	digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	delay(500);                        // wait for a half second
	test_serial();
}
