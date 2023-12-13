#include "flashTask.h"

static const char *TAG = "FLASH:";

/******************************************************************************************
 * 'flashTask' main function
 ******************************************************************************************/
void
flashTask(void *pvParameters)
{
	while(1)
	{
		if(xSemaphoreTake(xNandSemaphore, portMAX_DELAY) == pdTRUE)
		{
			ESP_LOGI(TAG, "NAND semaphore take"); //work with xSemaphoreGive(xNandSemaphore);
		}
	}
}
