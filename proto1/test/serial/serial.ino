void setup() {
	Serial.begin(115200);
	while (!Serial);
	Serial.println(F("Test Serial"));
}

void loop() {
	unsigned long start_usec, cur_usec;

	start_usec = micros();
	Serial.print(F("1"));
	cur_usec = micros();
	Serial.print(F("\t1 character: "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("1234567890"));
	cur_usec = micros();
	Serial.print(F("\t10 character: "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("123456789012"));
	cur_usec = micros();
	Serial.print(F("\t12 character: "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.println(F("1234567890"));
	cur_usec = micros();
	Serial.print(F("\t10 character + linefeed: "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");

	start_usec = micros();
	Serial.print(F("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	cur_usec = micros();
	Serial.print(F("\t120 character: "));
	Serial.print(cur_usec - start_usec);
	Serial.println(" usec");
}
