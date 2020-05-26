#include <IRremote.h>
#include "board.h"
#include "test.h"


IRrecv irrecv(A3);	// A3 pin

void setup()
{
    Serial.begin(115200);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
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

void loop()
{
    uint32_t ir_code = recv_ir();

    if (ir_code == 0) {
        return;
    }
    Serial.print("IR code = ");
    Serial.println(ir_code, HEX);
}

