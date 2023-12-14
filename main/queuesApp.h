#ifndef MAIN_QUEUESAPP_H_
#define MAIN_QUEUESAPP_H_

#include "appConfig.h"

extern QueueHandle_t     queueLedMode;
extern QueueHandle_t     queueNandStatus;
extern QueueHandle_t     queueNandPageBuffer;
extern SemaphoreHandle_t xNandSemaphore;

void createQueues(void);

#endif /* MAIN_QUEUESAPP_H_ */
