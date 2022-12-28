/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define BLINK_GPIO 2
#define BLINK_PERIOD	500

void app_main(void)
{
	uint8_t led_state = 0;
	int64_t start_usec, elapsed_usec;

	printf("configure to blink GPIO LED!\n");

	/* Set the GPIO as a push/pull output */
	gpio_reset_pin(BLINK_GPIO);
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

	while (1) {
		gpio_set_level(BLINK_GPIO, led_state);
		/* Toggle the LED state */
		led_state = !led_state;

		start_usec = esp_timer_get_time();
		printf("%d.%06d: %s\n", (int)(start_usec / 1000000), (int)(start_usec % 1000000),
				led_state == true ? "ON" : "OFF");

		start_usec = esp_timer_get_time();
		printf("1234567890");
		elapsed_usec = esp_timer_get_time() - start_usec;
		printf("\n 10 characters: %lld usec\n", elapsed_usec);

		start_usec = esp_timer_get_time();
		printf("1234567890123456789012345678901234567890");
		elapsed_usec = esp_timer_get_time() - start_usec;
		printf("\n 40 characters: %lld usec\n", elapsed_usec);

		start_usec = esp_timer_get_time();
		printf("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
		elapsed_usec = esp_timer_get_time() - start_usec;
		printf("\n 120 characters: %lld usec\n", elapsed_usec);

		start_usec = esp_timer_get_time();
		printf("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
		elapsed_usec = esp_timer_get_time() - start_usec;
		printf("\n 160 characters: %lld usec\n", elapsed_usec);

		start_usec = esp_timer_get_time();
		printf("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
		elapsed_usec = esp_timer_get_time() - start_usec;
		printf("\n 250 characters: %lld usec\n", elapsed_usec);

		vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);
	}
}
