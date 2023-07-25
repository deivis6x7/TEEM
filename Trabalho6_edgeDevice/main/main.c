/*
	Nome(s): 
      	Davi Salomão Soares Corrêa, 180118820.
      	Thiago de Deus Lima Rocha,  190020300.
 	Matéria: Tópicos especiais em engenharia mecatrônica - T01
  	Trabalho 6: Comunicação sem fio entre ESP32-Lora (sender communication)
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"

void task_tx(void *p)
{
   for(;;) {
      vTaskDelay(pdMS_TO_TICKS(5000));
      lora_send_packet((uint8_t*)"Hello bro!", 10);
      printf("packet sent...\n");
   }
}

void app_main()
{
   lora_init();
   lora_set_frequency(915e6);
   lora_enable_crc();
   xTaskCreate(&task_tx, "task_tx", 2048, NULL, 5, NULL);
}

/* 
    Referências:
        [1] sender_lora.c
        [2] Documentação: ESP32/FreeRTOS
        [3] Biblioteca Lora: https://github.com/Inteform/esp32-lora-library
*/
