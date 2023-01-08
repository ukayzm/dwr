/* GPIO Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "gpio.h"
#include "ir_receive.h"

void app_main(void)
{
	setup_gpio();
	setup_ir();

    while(1) {
		loop_gpio();
		loop_ir();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
