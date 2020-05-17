// 
//  Uses hardware serial to talk to the host computer and software serial 
//  for communication with the Bluetooth module
//  Intended for Bluetooth devices that require line end characters "\r\n"
//
//  Pins
//  Arduino 5V out TO BT VCC
//  Arduino GND to BT GND
//  Arduino A1 to BT RX through a voltage divider
//  Arduino A0 BT TX (no need voltage divider)
//
//  When a command is entered in the serial monitor on the computer 
//  the Arduino will relay it to the bluetooth module and display the result.
//


#include <SoftwareSerial.h>

SoftwareSerial BTserial(A0, A1); // RX | TX
const long baudRate = 38400;	// The baud rate in AT mode is always 38400.

#define MAX_CHAR	128
char buf[MAX_CHAR];
int buf_len = 0;

void setup() 
{
	Serial.begin(115200);
	Serial.print("Sketch:   ");   Serial.println(__FILE__);
	Serial.print("Uploaded: ");   Serial.println(__DATE__);
	Serial.println(" ");

	BTserial.begin(baudRate);  
	Serial.print("BTserial started at "); Serial.println(baudRate);
	Serial.print("> ");
}

void loop()
{
	// Read from the Bluetooth module and send to the Arduino Serial Monitor
	if (BTserial.available()) {
		char c = BTserial.read();
		Serial.write(c);
		if (c == '\n') {
			Serial.write("> ");
		}
	}

	// Read from the Serial Monitor and send to the Bluetooth module
	if (Serial.available()) {
		char c = Serial.read();
		if (buf_len < MAX_CHAR) {
			buf[buf_len++] = c;
		}
		Serial.write(c);
		if (buf_len == MAX_CHAR || c == '\n') {
			unsigned long start_usec = micros();
			for (int i = 0; i < buf_len; i++) {
				BTserial.write(buf[i]);   
			}
			unsigned long cur_usec = micros();
			Serial.print(buf_len);
			Serial.print(F(" chars sent in "));
			Serial.print(cur_usec - start_usec);
			Serial.println(F(" usec"));
			buf_len = 0;
		}
	}
}

