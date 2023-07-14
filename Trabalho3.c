/*  
	Nome: Davi Salomão Soares Corrêa
	Matrícula: 180118820
 	Matéria: Tópicos especiais em engenharia mecatrônica - T01
  	Trabalho 3: Análise do código sleep.c e proposta de solução
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h"

/*  Segundo [3], para garantir que a linha completa seja impressa 
    antes de entrar no modo de suspensão, é necessário aguardar 
    até que o FIFO de transmissão UART esteja vazio. */
void uart_tx_wait_idle(int uart_num)
{
    while (uart_tx_fifo_len(uart_num) > 0)
    {
       vTaskDelay(1 / portTICK_PERIOD_MS);  // 1 ms para verificar de novo
    }
}

void app_main()
{
    esp_sleep_enable_timer_wakeup(5000000); // configura o timer

    printf("Iniciando modo sleep... \n"); // mensagem informativa

    int64_t inicio = esp_timer_get_time(); // time stamp 1

    uart_tx_wait_idle(CONFIG_CONSOLE_UART_NUM); // espera até que UART esteja vazio

    esp_light_sleep_start(); // iniciando modo sleep

    int64_t fim = esp_timer_get_time(); // time stamp 2

    /*  as variáveis, depois e antes, definidas no printf 
        não correspondem as variáveis, fim e inicio, definidas anteriormente. */
    printf("Modo sleep durou %lld milisegundos.\n", (fim - inicio) / 1000);
    //printf("Modo sleep durou %lld milisegundos.\n", (depois - antes) / 1000);
}

/* 
    Referências:
        [1] sleep.c
        [2] Documentação: ESP32/FreeRTOS
        [3] Repositório: https://cpp.hotexamples.com/examples/-/-/esp_sleep_enable_timer_wakeup/cpp-esp_sleep_enable_timer_wakeup-function-examples.html
*/
