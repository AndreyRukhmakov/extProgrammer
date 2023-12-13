#ifndef MAIN_LEDTASK_H_
#define MAIN_LEDTASK_H_

typedef enum {
    usualBlink = 0,
    fastBlink,
    longBlink
}ledModeType;

void ledTask(void *pvParameters);

#endif /* MAIN_LEDTASK_H_ */
