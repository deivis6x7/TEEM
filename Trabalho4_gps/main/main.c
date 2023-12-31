/*  
	Nome: Davi Salomão Soares Corrêa
	Matrícula: 180118820
 	Matéria: Tópicos especiais em engenharia mecatrônica - T01
  Trabalho 04: Conexão do módulo GPS via comunicação serial 
*/

#include <stdio.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"

#define TXD_PIN 17
#define RXD_PIN 16

#define RX_BUF_SIZE 1024

char time[20];
char latitude[20];
char latitude_dir;
char longitude[20];
char longitude_dir;
char pos;

void parseGPSMessage(const char* message) {

  sscanf(message, "$GPRMC,%10[^,],%c,%14[^,],%c, %14[^,], %c", time, &pos, latitude, &latitude_dir, longitude, &longitude_dir);
  printf("-Tempo:        %s\n", time);
  printf("-Latitude:  %c %s\n", latitude_dir, latitude);
  printf("-Longitude: %c %s\n", longitude_dir, longitude);
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

  while (1) {
    char incoming_message[RX_BUF_SIZE];
    memset(incoming_message, 0, sizeof(incoming_message));
    uart_read_bytes(UART_NUM_1, (uint8_t *)incoming_message, RX_BUF_SIZE, pdMS_TO_TICKS(500));
    printf("Recebido:\n%s\n", incoming_message);
    parseGPSMessage(incoming_message);
  }
}

/* 
  Referências:
    [1] serial_loop.c
    [2] Documentação: ESP32/FreeRTOS
*/
