#include "queuesApp.h"

QueueHandle_t      queueLedMode;
SemaphoreHandle_t xNandSemaphore;


/******************************************************************************************
 * queues creation function
 ******************************************************************************************/
void createQueues(void)
{
	ledModeType ledMode = usualBlink;
	queueLedMode = xQueueCreate(1, sizeof(ledModeType));
	xQueueOverwrite(queueLedMode, &ledMode);

	xNandSemaphore = xSemaphoreCreateBinary();
}
