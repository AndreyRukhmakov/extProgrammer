#include "appConfig.h"

/******************************************************************************************
 * main function
 ******************************************************************************************/
void
app_main(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(nvs_flash_init());

    wifiStationInit();
    createQueues();

    xTaskCreate(ledTask,       "ledTask",       2048, NULL, 5, NULL);
    xTaskCreate(tcpServerTask, "tcpServerTask", 6144, NULL, 5, NULL);
    xTaskCreate(flashTask,     "flashTask",     4096, NULL, 5, NULL);
}
