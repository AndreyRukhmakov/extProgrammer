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

#ifndef JSON_HUMAN
#define JSON_HUMAN (JSON_INDENT(4) | JSON_SORT_KEYS)
#endif

/******************************************************************************************
 * Wi-Fi credentials
 ******************************************************************************************/
#define ESP_WIFI_STA_SSID      "olya"
#define ESP_WIFI_STA_PASSWD    "olya_522124"

/******************************************************************************************
 * TCP
 ******************************************************************************************/
#define TCP_RX_BUFFER_SIZE     2512U

/******************************************************************************************
 * LED GPIO
 ******************************************************************************************/
#define LED_PIN                2U

/******************************************************************************************
 * NAND GPIO
 ******************************************************************************************/
#define NAND_PAGE_SIZE         2048U

#define NAND_PIN_IO_0
#define NAND_PIN_IO_1
#define NAND_PIN_IO_2
#define NAND_PIN_IO_3
#define NAND_PIN_IO_4
#define NAND_PIN_IO_5
#define NAND_PIN_IO_6
#define NAND_PIN_IO_7

#define NAND_PIN_CE
#define NAND_PIN_ALE
#define NAND_PIN_CLE
#define NAND_PIN_RE
#define NAND_PIN_WE
#define NAND_PIN_R_B

#endif /* MAIN_APPCONFIG_H_ */
