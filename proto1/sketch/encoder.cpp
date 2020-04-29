#include "Arduino.h"
#include "encoder.h"


static int pinDir[NUM_ENCODER];
static int16_t nCount[NUM_ENCODER];
static uint32_t ulTotalCount[NUM_ENCODER];

static int numEncoder = 0;

static void isr0(void)
{
	if (digitalRead(pinDir[0]))
		nCount[0]++;
	else
		nCount[0]--;
	ulTotalCount[0]++;
}

static void isr1(void)
{
	if (digitalRead(pinDir[1]))
		nCount[1]--;
	else
		nCount[1]++;
	ulTotalCount[1]++;
}

Encoder::Encoder(int pin_intr, int pin_dir, int intr_per_rev)
{
	void (*isr)(void);
	id = numEncoder++;
	if (id == 0) {
		isr = isr0;
	} else if (id == 1) {
		isr = isr1;
	} else {
		Serial.println("too many encoder");
		return;
	}

	pinDir[id] = pin_dir;
	pinMode(pin_intr, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pin_intr), isr, FALLING);
	pinMode(pin_dir, INPUT_PULLUP);
	intrPerRevolution = intr_per_rev;

	Serial.print("Encoder PIN_INTR = ");
	Serial.print(pin_intr);
	Serial.print(", PIN_DIR = ");
	Serial.print(pin_dir);
	Serial.print(", intr_per_rev = ");
	Serial.print(intr_per_rev);
	Serial.println();
}

void Encoder::resetCount(void)
{
	nCount[id] = 0;
}

int16_t Encoder::getCountAndReset(void)
{
	int16_t count = nCount[id];
	nCount[id] = 0;
	return count;
}

int16_t Encoder::getIntrPerRevolution(void)
{
	return intrPerRevolution;
}

