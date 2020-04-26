#include "board.h"

#define SMOKE_TEST
#define SMOKE_TEST_SERIAL

void setup() {
#ifdef SMOKE_TEST
    pinMode(LED_BUILTIN, OUTPUT);
#ifdef SMOKE_TEST_SERIAL
    Serial.begin(9600);
#endif
#else
    setup_board();
#endif
}

void loop() {
#ifdef SMOKE_TEST
    digitalWrite(LED_BUILTIN, HIGH);
#ifdef SMOKE_TEST_SERIAL
    Serial.println("H");
#endif
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
#ifdef SMOKE_TEST_SERIAL
    Serial.println("L");
#endif
    delay(1000);
#else
    loop_board();
#endif
}
