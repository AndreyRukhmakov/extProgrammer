#include "appConfig.h"
#include "ledTask.h"

/******************************************************************************************
 * blinkTask - heartbeat LED task
 ******************************************************************************************/
void
ledTask(void *pvParameters)
{
	unsigned char ledMode = usualBlink;

	gpio_reset_pin((gpio_num_t)LED_PIN);
	gpio_set_direction((gpio_num_t)LED_PIN, GPIO_MODE_OUTPUT);

	while(1)
	{
		xQueuePeek(queueLedMode, &ledMode, 50);

		switch(ledMode)
		{
		case usualBlink:
			gpio_set_level(LED_PIN, 1);
			vTaskDelay(50 / portTICK_PERIOD_MS);
			gpio_set_level(LED_PIN, 0);
			vTaskDelay(5000 / portTICK_PERIOD_MS);
			break;
		case fastBlink:
			gpio_set_level(LED_PIN, 1);
			vTaskDelay(50 / portTICK_PERIOD_MS);
			gpio_set_level(LED_PIN, 0);
			vTaskDelay(200 / portTICK_PERIOD_MS);
			break;
		case longBlink:
			gpio_set_level(LED_PIN, 1);
			vTaskDelay(2000 / portTICK_PERIOD_MS);
			gpio_set_level(LED_PIN, 0);
			vTaskDelay(2000 / portTICK_PERIOD_MS);
			break;
		default:
			break;
		}

	}
}
