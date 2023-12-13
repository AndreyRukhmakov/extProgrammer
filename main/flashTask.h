#ifndef MAIN_FLASHTASK_H_
#define MAIN_FLASHTASK_H_

#include "appConfig.h"

typedef struct {
	enum {
		busy = 0,
		done
	} statusType;
	char data[2048];
}flashStatusType;

void flashTask(void *pvParameters);

#endif /* MAIN_FLASHTASK_H_ */
