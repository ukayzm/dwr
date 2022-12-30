#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "led_state.h"


#define LOOP_PERIOD		100
#define LOOP_WRAP		20

static PAIRING_STATE pairing_state;
static int count;
static uint32_t status[] = {
	0b10000000001000000000,
	0b10101010101010101010,
	0b11000110001100011000,
	0b11111111110000000000,
};

char *pairing_state_string(int ps)
{
#define str(s)	case s: return #s
	switch (ps) {
		str(PAIRING_STATE_SCANNING);
		str(PAIRING_STATE_CONNECTING);
		str(PAIRING_STATE_CONNECTED);
		default:
			break;
	}
	return "???";
}

void set_pairing_led_state(PAIRING_STATE new_state)
{
	if (new_state != pairing_state) {
		count = 0;
		pairing_state = new_state;
		printf("\n");
		int64_t cur_usec = esp_timer_get_time();
		printf("%d.%06d: %s -------------------\n",
				(int)(cur_usec / 1000000), (int)(cur_usec % 1000000),
				pairing_state_string(pairing_state));
		printf("\n");
	}
}

void loop_led_state(void)
{
	count++;
	count = count % LOOP_WRAP;
	int output = (status[pairing_state] >> ((LOOP_WRAP - 1) - count)) & 0x1;
	gpio_set_level(BLINK_GPIO, output);
}

void led_state_task(void *param)
{
	count = 0;
	while (1) {
		loop_led_state();
		vTaskDelay(LOOP_PERIOD / portTICK_PERIOD_MS);
	}
}

void setup_led_state(void)
{
	/* Set the GPIO as a push/pull output */
	gpio_reset_pin(BLINK_GPIO);
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(&led_state_task, "led_state_task", 6 * 1024, NULL, 2, NULL);
}
