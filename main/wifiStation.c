#include "wifiStation.h"
#include "appConfig.h"

#define ESP_MAXIMUM_RETRY                    5U
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD    WIFI_AUTH_WPA2_PSK
#define WIFI_CONNECTED_BIT                   BIT0
#define WIFI_FAIL_BIT                        BIT1

static const char *TAG      = "WiFi:";
int                retryNum = 0;

/* FreeRTOS event group to signal when we are connected/disconnected */
static EventGroupHandle_t sWifiEventGroup;


/******************************************************************************************
 * Init as 'station' config function
 ******************************************************************************************/
esp_netif_t *
wifiInitStation(void)
{
    esp_netif_t *espNetifSta = esp_netif_create_default_wifi_sta();

    wifi_config_t wifiStaConfig = {
        .sta = {
            .ssid = ESP_WIFI_STA_SSID,
            .password = ESP_WIFI_STA_PASSWD,
            .scan_method = WIFI_ALL_CHANNEL_SCAN,
            .failure_retry_cnt = ESP_MAXIMUM_RETRY,
            .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifiStaConfig) );

    return espNetifSta;
}

/******************************************************************************************
 * WiFi event handler function
 ******************************************************************************************/
void
wifiEventHandler(void             *arg,
                 esp_event_base_t  eventBase,
                 int32_t           eventId,
                 void             *eventData)
{
    if (eventBase == WIFI_EVENT && eventId == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
        ESP_LOGI(TAG, "Station started");
    }
    else if (eventBase == IP_EVENT && eventId == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) eventData;
        ESP_LOGI(TAG, "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));
        retryNum = 0;
        xEventGroupSetBits(sWifiEventGroup, WIFI_CONNECTED_BIT);
    }
}

/******************************************************************************************
 * WiFi station main init function
 ******************************************************************************************/
void
wifiStationInit(void)
{
    sWifiEventGroup = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                    ESP_EVENT_ANY_ID,
                    &wifiEventHandler,
                    NULL,
                    NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                    IP_EVENT_STA_GOT_IP,
                    &wifiEventHandler,
                    NULL,
                    NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    esp_netif_t *espNetifSta = wifiInitStation();
    ESP_ERROR_CHECK(esp_wifi_start());

    EventBits_t bits = xEventGroupWaitBits(sWifiEventGroup,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT)
    {
        ESP_LOGI(TAG, "Connected to SSID: %s", ESP_WIFI_STA_SSID);
    }
    else if (bits & WIFI_FAIL_BIT)
    {
        ESP_LOGI(TAG, "Failed to connect to SSID: %s", ESP_WIFI_STA_SSID);
    }
    else
    {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
        return;
    }

    esp_netif_set_default_netif(espNetifSta);
}
