#include "tcpServerTask.h"
#include "appConfig.h"

#define PORT                  8888U
#define KEEPALIVE_IDLE        5U   //TCP keep-alive idle time(s)
#define KEEPALIVE_INTERVAL    5U   //TCP keep-alive interval time(s)
#define KEEPALIVE_COUNT       3U   //TCP keep-alive packet retry send counts

static const char *TAG = "TCP:";

typedef enum {
    firstSector = 0,
    someSector,
    lastSector,
	stop
} progressType;

/******************************************************************************************
 * JSON content parser
 ******************************************************************************************/
void
dataParse(unsigned char *data, int dataLen)
{
    json_error_t error;
    json_t *status        = NULL;
    progressType progress = stop;
    int pageNumber        = 0;

	json_t *obj = json_loadb((const char *)data, dataLen, JSON_ALLOW_NUL, &error);

    if (NULL == obj)
    {
    	ESP_LOGE(TAG, "Error 'json_loadb' - %s", error.text);
    	goto EXIT;
	}

    status = json_object_get(obj, "status");

    if (NULL == status)
    {
    	ESP_LOGE(TAG, "Unable to get JSON key 'status'");
    	goto EXIT;
	}

    if (0 == strcmp(json_string_value(status), "first sector"))
    {
    	progress = firstSector;
    }
    else if (0 == strcmp(json_string_value(status), "some sector"))
    {
    	progress = someSector;
    }
    else if (0 == strcmp(json_string_value(status), "last sector"))
    {
    	progress = lastSector;
    }
    else
    {
    	ESP_LOGE(TAG, "Unknown process type.");
    	goto EXIT;
    }

    if (NULL == json_object_get(obj, "page number"))
    {
    	ESP_LOGE(TAG, "Unable to get JSON key 'pageNumber'");
    	goto EXIT;
	}

    pageNumber = json_integer_value(json_object_get(obj, "page number"));


EXIT:
    json_decref(obj);
}

/******************************************************************************************
 * Incoming data processing
 ******************************************************************************************/
void
dataProcessing(const int sock)
{
    int len;
    unsigned char rxBuffer[TCP_RX_BUFFER_SIZE];

    memset(rxBuffer, 0, sizeof(rxBuffer));
    len = recv(sock, rxBuffer, sizeof(rxBuffer) - 1, 0);

    if (len < 0)
    {
        ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
    }
    else if (0 == len)
    {
        ESP_LOGW(TAG, "Connection closed");
    }
    else
    {
        ESP_LOGI(TAG, "Received %d bytes: %s", len, rxBuffer);

        dataParse(rxBuffer, len);

        int written = send(sock, "ESP32 response: JSON successfully received.",
        		           strlen("ESP32 response: JSON successfully received."), 0);

        if (written < 0)
        {
            ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
            return;
        }
    }
}

/******************************************************************************************
 * 'tcpServerTask' main function
 ******************************************************************************************/
void
tcpServerTask(void *pvParameters)
{
    char addrStr[128] = {0};
    int addrFamily    = AF_INET;
    int ipProtocol   = 0;
    int keepAlive     = 1;
    int keepIdle      = KEEPALIVE_IDLE;
    int keepInterval  = KEEPALIVE_INTERVAL;
    int keepCount     = KEEPALIVE_COUNT;
    struct sockaddr_storage dest_addr;

    if (addrFamily == AF_INET)
    {
        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr    = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family         = AF_INET;
        dest_addr_ip4->sin_port           = htons(PORT);
        ipProtocol                        = IPPROTO_IP;
    }


    int listen_sock = socket(addrFamily, SOCK_STREAM, ipProtocol);

    if (listen_sock < 0)
    {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }

    int opt = 1;

    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    if (err != 0)
    {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", addrFamily);
        goto EXIT;
    }

    ESP_LOGI(TAG, "Socket bound, port %d", PORT);

    err = listen(listen_sock, 1);

    if (err != 0)
    {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        goto EXIT;
    }

    while (1)
    {
        ESP_LOGI(TAG, "Socket listening");

        struct sockaddr_storage source_addr;
        socklen_t addr_len = sizeof(source_addr);
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);

        if (sock < 0)
        {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        setsockopt(sock, SOL_SOCKET,  SO_KEEPALIVE,  &keepAlive,    sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE,  &keepIdle,     sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT,   &keepCount,    sizeof(int));

        // Convert ip address to string
        if (source_addr.ss_family == PF_INET)
        {
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addrStr, sizeof(addrStr) - 1);
        }

        ESP_LOGI(TAG, "Accepted ip: %s", addrStr);

        dataProcessing(sock);

        shutdown(sock, 0);
        close(sock);
    }

EXIT:
    close(listen_sock);
    vTaskDelete(NULL);
}
