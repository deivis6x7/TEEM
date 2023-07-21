/*  
  Nome: Davi Salomão Soares Corrêa
  Matrícula: 180118820
  Matéria: Tópicos especiais em engenharia mecatrônica - T01
  Trabalho 04: Conexão do módulo GPS via comunicação serial e WebServer
*/

#include <stdio.h>
#include "connect.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_http_server.h"

#include "driver/uart.h"
#include "string.h"

#define TXD_PIN 17
#define RXD_PIN 16

#define RX_BUF_SIZE 1024

static const char *TAG = "SERVER";


static esp_err_t on_default_url(httpd_req_t *req)
{
    char time[20];
    char latitude[20];
    char latitude_dir;
    char longitude[20];
    char longitude_dir;
    char pos;
    char out[200] = "Tempo: ";
    ESP_LOGI(TAG,"URL: %s",req->uri);

    char incoming_message[RX_BUF_SIZE];
    memset(incoming_message, 0, sizeof(incoming_message));
    uart_read_bytes(UART_NUM_1, (uint8_t *)incoming_message, RX_BUF_SIZE, pdMS_TO_TICKS(500));
    sscanf(incoming_message, "$GPRMC,%10[^,],%c,%14[^,],%c, %14[^,], %c", time, &pos, latitude, &latitude_dir, longitude, &longitude_dir);
    strcat(out, time);
    strcat(out, "<br>Latitude: ");
    strcat(out, latitude);
    strcat(out, "<br>Longitude: ");
    strcat(out, longitude);
    //printf("Recebido:\n%s\n", incoming_message);
    httpd_resp_sendstr(req, out);
    
    return ESP_OK;
}

static void init_server()
{
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  ESP_ERROR_CHECK(httpd_start(&server, &config));

  httpd_uri_t default_url = {
    .uri ="/",
    .method = HTTP_GET,
    .handler = on_default_url
  };
  httpd_register_uri_handler(server,&default_url);

}

void app_main(void)
{
  uart_config_t uart_config = {
    .baud_rate = 9600,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  uart_param_config(UART_NUM_1, &uart_config);
  uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART_NUM_1, RX_BUF_SIZE, 0, 0, NULL, 0);

  ESP_ERROR_CHECK(nvs_flash_init());
  wifi_init();
  // atualize de acordo com seu SSID e a sua senha Wi-Fi
  //ESP_ERROR_CHECK(wifi_connect_sta("TP-Link_BA20", "90227820", 10000));

  init_server();
}

/* 
  Referências:
    [1] serial_loop.c
    [2] webServer.c
    [3] Documentação: ESP32/FreeRTOS
*/