//#define IR_SMALLD_NEC
#define IR_SMALLD_NECx
//#define IR_SMALLD_RC5
//#define IR_SMALLD_SIRC12
//#define IR_SMALLD_SIRC15
//#define IR_SMALLD_SIRC20
//#define IR_SMALLD_SIRC
//#define IR_SMALLD_SAMSUNG
//#define IR_SMALLD_SAMSUNG32
#include <IRsmallDecoder.h>
IRsmallDecoder irDecoder(3);
irSmallD_t irData;

void setup() {
	Serial.begin(115200);
	Serial.println("Waiting for a NEC remote control IR signal...");
	Serial.println("msec\t held \t addr \t cmd");
}

void loop() {
	if(irDecoder.dataAvailable(irData)) {
		Serial.print((float)millis() / 1000);
		Serial.print("\t ");
		Serial.print(irData.keyHeld,HEX);
		Serial.print("\t ");
		Serial.print(irData.addr,HEX);
		Serial.print("\t ");
		Serial.println(irData.cmd,HEX);
	}
}
