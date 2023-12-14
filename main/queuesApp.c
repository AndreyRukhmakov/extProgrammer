#include "queuesApp.h"

QueueHandle_t      queueLedMode;
QueueHandle_t      queueNandStatus;
QueueHandle_t      queueNandPageBuffer;
SemaphoreHandle_t  xNandSemaphore;


/******************************************************************************************
 * queues creation function
 ******************************************************************************************/
void createQueues(void)
{
	unsigned char ledMode = usualBlink;
	queueLedMode = xQueueCreate(1, sizeof(unsigned char));
	xQueueOverwrite(queueLedMode, &ledMode);

	unsigned char nandStatus = nandIsReady;
	queueNandStatus = xQueueCreate(1, sizeof(unsigned char));
	xQueueOverwrite(queueNandStatus, &nandStatus);

	queueNandPageBuffer = xQueueCreate(1, NAND_PAGE_SIZE);

	xNandSemaphore = xSemaphoreCreateBinary();
}
