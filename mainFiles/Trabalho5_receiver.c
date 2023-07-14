/*  
	Nome(s): 
      Davi Salomão Soares Corrêa, 180118820.
      Thiago de Deus Lima Rocha,  190020300.
 	Matéria: Tópicos especiais em engenharia mecatrônica - T01
  	Trabalho 5: Comunicação sem fio entre ESP32-Lora (receiver communication)
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"

uint8_t buffer[32];

void task_rx(void *p)
{
   int x;
   for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
         x = lora_receive_packet(buffer, sizeof(buffer));
         buffer[x] = 0;
         printf("Received: %s\n", buffer);
         lora_receive();
      }
      vTaskDelay(1);
   }
}

void app_main()
{
   lora_init();
   lora_set_frequency(915e6);
   lora_enable_crc();
   xTaskCreate(&task_rx, "task_rx", 2048, NULL, 5, NULL);
}

/* 
    Referências:
        [1] receiver_lora.c
        [2] Documentação: ESP32/FreeRTOS
        [3] Biblioteca Lora: https://github.com/Inteform/esp32-lora-library
*/
