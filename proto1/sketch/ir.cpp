#include <IRremote.h>
#include "board.h"
#include "test.h"


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
        Serial.println(F("^"));
		motor0.incRpmPercent(10);
		motor1.incRpmPercent(10);
    } else if (ir_code == 0x26e6c1ca) {
        Serial.println(F("v"));
		motor0.incRpmPercent(-10);
		motor1.incRpmPercent(-10);
    } else if (ir_code == 0x6d89e538) {
        Serial.println(F(">"));
		motor0.incRpmPercent(10);
		motor1.incRpmPercent(-10);
    } else if (ir_code == 0xdad4e90b) {
        Serial.println(F("<"));
		motor0.incRpmPercent(-10);
		motor1.incRpmPercent(10);
    } else if (ir_code == 0x7d399127) {
        Serial.println(F("OK"));
		motor0.setRpm(0);
		motor1.setRpm(0);
    } else if (ir_code == 0xd7d018ec) {
        Serial.println(F("VOL+"));
		motor0.incKd(1);
		motor1.incKd(1);
    } else if (ir_code == 0xf49b208a) {
        Serial.println(F("VOL-"));
		motor0.incKd(-1);
		motor1.incKd(-1);
    } else if (ir_code == 0x68a199f0) {
        Serial.println(F("REC"));
		motor0.incKi(1);
		motor1.incKi(1);
    } else if (ir_code == 0xf169e8b2) {
        Serial.println(F("REPLAY"));
		motor0.incKi(-1);
		motor1.incKi(-1);
    } else if (ir_code == 0xcf98a7b6) {
        Serial.println(F("CH+"));
		motor0.incKp(1);
		motor1.incKp(1);
    } else if (ir_code == 0x107f5e27) {
        Serial.println(F("CH-"));
		motor0.incKp(-1);
		motor1.incKp(-1);
    } else if (ir_code == 0x32939470) {
        Serial.println(F("PLAY/PAUSE"));
    } else if (ir_code == 0x16d5cb04) {
        Serial.println(F("FF"));
    } else if (ir_code == 0x19fd189b) {
        Serial.println(F("REW"));
    } else if (ir_code == 0x407e2e01) {
        Serial.println(F("STOP"));
    } else if (ir_code == 0x7547960e) {
        Serial.println(F("NEXT"));
    } else if (ir_code == 0xd1921028) {
        Serial.println(F("PREV"));
    } else if (ir_code == 0x26ecbcf3) {
        Serial.println(F("(0)"));
		start_test_mpu6050();
    } else if (ir_code == 0x9004b206) {
        Serial.println(F("(1)"));
		start_test_motor_dir(&motor0);
    } else if (ir_code == 0xc35f14b9) {
        Serial.println(F("(2)"));
		start_test_motor_dir(&motor1);
    } else if (ir_code == 0xa6034632) {
        Serial.println(F("(3)"));
		start_test_motor_pwm(&motor0);
    } else if (ir_code == 0x45897fb8) {
        Serial.println(F("(4)"));
		start_test_motor_pwm(&motor1);
    } else if (ir_code == 0x6a8bf890) {
        Serial.println(F("(5)"));
		start_test_motor_rpm(&motor0);
    } else if (ir_code == 0x08a2cf97) {
        Serial.println(F("(6)"));
		start_test_motor_rpm(&motor1);
    } else if (ir_code == 0x462c837e) {
        Serial.println(F("(7)"));
		start_test_encoder();
    } else if (ir_code == 0x42c5c050) {
        Serial.println(F("(8)"));
    } else if (ir_code == 0x67c83928) {
        Serial.println(F("(9)"));
    } else if (ir_code == 0x6bef8366) {
        Serial.println(F("PWR"));
    } else if (ir_code == 0xbe663d0a) {
        Serial.println(F("MUTE"));
    } else if (ir_code == 0xae7fbf1d) {
        Serial.println(F("TEXT"));
    } else {
        Serial.println(ir_code, HEX);
    }
    last_ir_ms = millis();
    last_ir_code = ir_code;
}

