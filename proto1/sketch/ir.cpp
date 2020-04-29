#include <IRremote.h>
#include "board.h"
#include "test_motor.h"


IRrecv irrecv(IR_PIN);

void setup_ir()
{
    irrecv.enableIRIn(); // Start the receiver
}

uint32_t recv_ir()
{
    decode_results results;
    results.value = 0;
    if (irrecv.decode(&results)) {
        irrecv.resume(); // Receive the next value
    }
    return results.value;
}

void loop_ir()
{
    uint32_t ir_code;
    static uint32_t last_ir_code;
    static uint32_t last_ir_ms;

    ir_code = recv_ir();

    if (ir_code == 0) {
        return;
    }
    if (ir_code != 0x4de93dc4 && ir_code != 0x26e6c1ca && ir_code != 0x6d89e538 && ir_code != 0xdad4e90b) {
        if ((last_ir_ms + 250 > millis()) && (ir_code == last_ir_code)) {
            return;
        }
    }

    if (ir_code == 0x4de93dc4) {
        Serial.println("^");
    } else if (ir_code == 0x26e6c1ca) {
        Serial.println("v");
    } else if (ir_code == 0x6d89e538) {
        Serial.println(">");
    } else if (ir_code == 0xdad4e90b) {
        Serial.println("<");
    } else if (ir_code == 0x7d399127) {
        Serial.println("OK");
    } else if (ir_code == 0x68a199f0) {
        Serial.println("REC");
    } else if (ir_code == 0xf169e8b2) {
        Serial.println("REPLAY");
    } else if (ir_code == 0xcf98a7b6) {
        Serial.println("CH+");
    } else if (ir_code == 0x107f5e27) {
        Serial.println("CH-");
    } else if (ir_code == 0xd7d018ec) {
        Serial.println("VOL+");
    } else if (ir_code == 0xf49b208a) {
        Serial.println("VOL-");
    } else if (ir_code == 0x32939470) {
        Serial.println("PLAY/PAUSE");
    } else if (ir_code == 0x16d5cb04) {
        Serial.println("FF");
    } else if (ir_code == 0x19fd189b) {
        Serial.println("REW");
    } else if (ir_code == 0x407e2e01) {
        Serial.println("STOP");
    } else if (ir_code == 0x7547960e) {
        Serial.println("NEXT");
		start_test_motor_speed(&leftMotor);
    } else if (ir_code == 0xd1921028) {
        Serial.println("PREV");
		start_test_motor_speed(&rightMotor);
    } else if (ir_code == 0x26ecbcf3) {
        Serial.println("(0)");
    } else if (ir_code == 0x9004b206) {
        Serial.println("(1)");
		start_test_motor_dir(&leftMotor);
    } else if (ir_code == 0xc35f14b9) {
        Serial.println("(2)");
		start_test_motor_dir(&rightMotor);
    } else if (ir_code == 0x6bef8366) {
        Serial.println("PWR");
    } else if (ir_code == 0xbe663d0a) {
        Serial.println("MUTE");
    } else if (ir_code == 0xae7fbf1d) {
        Serial.println("TEXT");
    } else {
        Serial.println(ir_code, HEX);
    }
    last_ir_ms = millis();
    last_ir_code = ir_code;
}

