#include "flashTask.h"

static const char *TAG = "FLASH:";

#define NAND_FLASH()    vTaskDelay(2000 / portTICK_PERIOD_MS)

/******************************************************************************************
 * 'flashTask' main function
 ******************************************************************************************/
void
flashTask(void *pvParameters)
{
	unsigned char nandStatus = nandIsReady;
	unsigned char ledMode    = usualBlink;
	char pageBuff[NAND_PAGE_SIZE];

	while(1)
	{
		if(xSemaphoreTake(xNandSemaphore, portMAX_DELAY) == pdTRUE)
		{
			nandStatus = nandIsBusy;
			xQueueOverwrite(queueNandStatus, &nandStatus);

			xQueuePeek(queueNandPageBuffer, pageBuff, (TickType_t)100);
			ESP_LOGI(TAG, "WILL BE WRITTEN TO NAND: %s", pageBuff);

			ledMode = fastBlink;
			xQueueOverwrite(queueLedMode, &ledMode);

			NAND_FLASH();

			ledMode = usualBlink;
			xQueueOverwrite(queueLedMode, &ledMode);

			nandStatus = nandIsReady;
			xQueueOverwrite(queueNandStatus, &nandStatus);
		}
	}
}
