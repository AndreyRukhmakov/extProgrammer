#include "flashTask.h"

static const char *TAG = "FLASH:";

#define NAND_FLASH()

/******************************************************************************************
 * 'flashTask' main function
 ******************************************************************************************/
void
flashTask(void *pvParameters)
{
	unsigned char nandStatus = nandIsReady;
	char pageBuff[NAND_PAGE_SIZE];

	vTaskDelay(50 / portTICK_PERIOD_MS);
	nandGpioInit();
	nandReadId();

	while(1)
	{
		if(xSemaphoreTake(xNandSemaphore, portMAX_DELAY) == pdTRUE)
		{
			nandStatus = nandIsBusy;
			xQueueOverwrite(queueNandStatus, &nandStatus);

			xQueuePeek(queueNandPageBuffer, pageBuff, (TickType_t)100);
//			ESP_LOGI(TAG, "WILL BE WRITTEN TO NAND: %s", pageBuff);

			NAND_FLASH();

			nandStatus = nandIsReady;
			xQueueOverwrite(queueNandStatus, &nandStatus);
		}
	}
}
