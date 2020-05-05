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
		Serial.println(F("too many encoder"));
		return;
	}

	pinDir[id] = pin_dir;
	pinMode(pin_intr, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pin_intr), isr, FALLING);
	pinMode(pin_dir, INPUT_PULLUP);
	intrPerRevolution = intr_per_rev;
	q_index = 0;
}

void Encoder::resetCount(void)
{
	nCount[id] = 0;
}

int16_t Encoder::getCountAndReset(unsigned long usec)
{
	int16_t count = nCount[id];
	nCount[id] = 0;

	q_count[q_index] = count;
	q_usec[q_index] = usec;
	q_index++;
	q_index %= MAX_QUEUE;
	return count;
}

int16_t Encoder::getCurRpm(void)
{
	int16_t count = 0;
	for (int i = 0; i < MAX_QUEUE; i++) {
		if (i != q_index) {
			count += q_count[i];
		}
	}
	long dt = q_usec[(q_index + MAX_QUEUE - 1) % MAX_QUEUE] - q_usec[q_index];
	if (dt <= 0) {
		return 0;
	}
	return (double)(count * 60) / intrPerRevolution * 1000000 / dt;
}

