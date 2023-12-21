#ifndef MAIN_APPCONFIG_H_
#define MAIN_APPCONFIG_H_

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include <sys/param.h>
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif_net_stack.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/lwip_napt.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "wifiStation.h"
#include "jansson.h"
#include "driver/gpio.h"
#include "queuesApp.h"
#include "ledTask.h"
#include "tcpServerTask.h"
#include "flashTask.h"
#include "nand.h"

#ifndef JSON_HUMAN
#define JSON_HUMAN (JSON_INDENT(4) | JSON_SORT_KEYS)
#endif

typedef enum {
    nandIsReady = 0,
	nandIsBusy,
	error,
	readyToFlash,
    startFlash,
	flashing,
	stopFlash,
	jsonError,
	jsonIsUnknown,
	ok
}state;

typedef enum {
    usualBlink = 0,
    fastBlink,
    longBlink
}ledMode;

/******************************************************************************************
 * Wi-Fi credentials
 ******************************************************************************************/
#define ESP_WIFI_STA_SSID      "your_wifi"
#define ESP_WIFI_STA_PASSWD    "your_password"

/******************************************************************************************
 * TCP
 ******************************************************************************************/
#define PORT                   8888U

/******************************************************************************************
 * LED GPIO
 ******************************************************************************************/
#define LED_PIN                2U

/******************************************************************************************
 * NAND
 ******************************************************************************************/
#define NAND_PAGE_SIZE         2048U

#define NAND_PIN_IO_0           4U
#define NAND_PIN_IO_1          13U
#define NAND_PIN_IO_2          32U
#define NAND_PIN_IO_3          33U
#define NAND_PIN_IO_4          25U
#define NAND_PIN_IO_5          26U
#define NAND_PIN_IO_6          27U
#define NAND_PIN_IO_7          14U

#define NAND_PIN_CE             5U // Chip Enable
#define NAND_PIN_ALE           18U // Address latch
#define NAND_PIN_CLE           23U // Command latch
#define NAND_PIN_RE            22U // Read enable
#define NAND_PIN_WE            21U // Write enable
#define NAND_PIN_RB            19U // Read/Busy

#endif /* MAIN_APPCONFIG_H_ */
